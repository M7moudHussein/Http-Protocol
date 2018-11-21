#include <utility>
#include <iostream>
#include <file_reader.h>
#include "server_worker.h"

void *handle_request(void *thread_arguments);

response handle_get_request(request *request_to_process);

response handle_post_request(request *request_to_process);

void handle_post_followers(request *request_to_process, int socket_no);

server_worker::server_worker(request request_to_process, int socket_no) {
    this->request_to_process = std::move(request_to_process);
    this->socket_no = socket_no;
}

void server_worker::process_request() {
    thread_args *args = new thread_args();
    args->socket_no = socket_no;
    args->request_to_process = request_to_process;
    int rc = pthread_create(new pthread_t, nullptr, handle_request, args);
}


void *handle_request(void *arguments) {
    thread_args *args = (thread_args *) arguments;
    request *request_to_process = args->request_to_process;
    int socket_no = args->socket_no;

    response res;
    if (request_to_process->get_method() == POST) {
        res = handle_post_request(request_to_process);
    } else {
        res = handle_get_request(request_to_process);
    }

    std::string response_message = res.build_response_message();
    std::cout << response_message << std::endl;
    send(socket_no, response_message.c_str(), response_message.length(), 0);

    if (request_to_process->get_method() == POST) {
        handle_post_followers(request_to_process, socket_no);
    }
    delete args;
}

response handle_get_request(request *request_to_process) {
    std::string file_data;
    int data_length;
    file_reader reader;
    data_length = reader.read_file(request_to_process->get_url(), &file_data);

    response res;
    res.set_http_version(request_to_process->get_http_version());

    if (data_length == -1) {
        res.set_status(CODE_404);
        res.set_content_length(0);
    } else {
        res.set_status(CODE_200);
        res.set_body(file_data);
        res.set_content_type(http_utils::get_content_type(request_to_process->get_url()));
        res.set_content_length(reader.get_file_size(request_to_process->get_url()));
    }
    return res;
}

response handle_post_request(request *request_to_process) {
    response res;
    res.set_status(CODE_200);
    res.set_http_version(request_to_process->get_http_version());
    res.set_content_length(0);
    return res;
}

void handle_post_followers(request *request_to_process, int socket_no) {
    char *file_data = new char[request_to_process->get_content_length()];
    int total_read = 0;
    while (total_read < request_to_process->get_content_length()) {
        int bytes_read = recv(socket_no, file_data, request_to_process->get_content_length(), 0);
        if (bytes_read == -1) {
            perror("Error while receiving data");
            break;
        }
        total_read += bytes_read;
        file_writer writer;
        writer.write(request_to_process->get_url().c_str(), std::string(file_data, bytes_read));
    }
    delete[] file_data;
}