#include <utility>
#include <iostream>
#include <file_reader.h>
#include <thread>
#include <zconf.h>
#include <sys/socket.h>
#include <cstring>
#include "server_worker.h"

server_worker::server_worker(int socket_no) {
    this->socket_no = socket_no;
    post_in_queue = false;
    has_timed_out = false;
}

void server_worker::start() {
    new std::thread(&server_worker::retrieve_requests, this);
    new std::thread(&server_worker::process_requests, this);
}


void server_worker::retrieve_requests() {
    fd_set read_fds;
    struct timeval tv{};
    while (true) {
        if (post_in_queue) {
            continue;
        }
        FD_ZERO(&read_fds);
        FD_SET(socket_no, &read_fds);
        tv.tv_sec = 10;
        tv.tv_usec = 0;
        int activity = select(socket_no + 1, &read_fds, NULL, NULL, &tv);
        if (activity == -1) {
            perror("Error while waiting for new requests");
            close(socket_no);
            exit(EXIT_FAILURE);
        } else if (activity == 0) {
            std::cout << "Connection timeout, No More Requests Received" << std::endl;
            has_timed_out = true;
            exit(0);
        } else if (activity > 0 && FD_ISSET(socket_no, &read_fds)) {
            pull_requests();
        }
    }
}

void server_worker::pull_requests() {
    ssize_t read_bytes = recv(socket_no, this->request_buffer, REQUEST_BUFFER_SIZE, 0);

    if(read_bytes == 0)
        return;
    else if (read_bytes < 0) {
        perror("Error while reading from socket");
        return;
    }
    std::cout << "Request received: " << std::endl;
    std::cout << "*****\n" << request_buffer << "*******" << std::endl;
    std::vector<size_t> header_ends = http_utils::findHeaderEnds(request_buffer);
    std::string buffer_string = std::string(request_buffer, read_bytes);
    size_t prev_pos = 0;
    for (size_t req_start_pos : header_ends) {
        std::string req_string = buffer_string.substr(prev_pos, req_start_pos + 4);
        std::cout << "+++++" << req_string << "+++++" << "\n";
        request *req = new request();
        req->build_header(req_string);
        this->requests_queue.push(req);
        if (req->get_method() == POST) {
            post_in_queue = true;
        }
        prev_pos = req_start_pos + 4;
    }
}

void server_worker::process_requests() {
    while (!has_timed_out || !requests_queue.empty()) {
        if (!requests_queue.empty()) {
            request *req = requests_queue.front();
            requests_queue.pop();
            response *res = nullptr;
            switch (req->get_method()) {
                case GET:
                    res = handle_get_request(req);
                    break;
                case POST:
                    res = handle_post_request(req);
                    break;
            }

            std::string response_message = res->build_response_message();
            std::string method = req->get_method() == GET ? "GET" : "POST";

            std::cout << "Response for " << method << " sent: " << std::endl;
            std::cout << response_message << std::endl;

            send(socket_no, response_message.c_str(), response_message.length(), 0);

            if (req->get_method() == POST) {
                handle_post_followers(req);
            }
            delete req;
            delete res;
        }
    }
    close(socket_no);
}

response *server_worker::handle_get_request(request *request_to_process) {
    std::string file_data;
    int data_length;
    file_reader reader;
    data_length = reader.read_file(request_to_process->get_url(), &file_data);

    response *res = new response();
    res->set_http_version(request_to_process->get_http_version());

    if (data_length == -1) {
        res->set_status(CODE_404);
        res->set_content_length(0);
    } else {
        res->set_status(CODE_200);
        res->set_body(file_data);
        res->set_content_type(http_utils::get_content_type(request_to_process->get_url()));
        res->set_content_length(reader.get_file_size(request_to_process->get_url()));
    }
    return res;
}

response *server_worker::handle_post_request(request *request_to_process) {
    response *res = new response();
    res->set_status(CODE_200);
    res->set_http_version(request_to_process->get_http_version());
    res->set_content_length(0);

    return res;
}

void server_worker::handle_post_followers(request *request_to_process) {
    int total_read = 0;
    while (total_read < request_to_process->get_content_length()) {
        ssize_t bytes_read = recv(socket_no, request_buffer, REQUEST_BUFFER_SIZE, 0);
        if (bytes_read == -1) {
            perror("Error while receiving data");
            break;
        }
        total_read += bytes_read;
        file_writer writer;
        writer.write(request_to_process->get_url(), std::string(request_buffer, bytes_read));
    }
    post_in_queue = false;
}
