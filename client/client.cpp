#include <file_reader.h>
#include <iostream>
#include <zconf.h>
#include <asm/ioctls.h>
#include <sys/ioctl.h>
#include "client.h"

/* Initiate client environment */
client::client(std::string server_ip) {
    client::server_ip = server_ip;
    response_buffer = new char[MAX_BUFFER_SIZE];
    this->post_in_process = false;
    this->is_last_request = false;
}

/* Starts associated threads */
void client::start() {
    receiver_thread = new std::thread(&client::process_response, this);
}

/* Connects to server */
bool client::establish_connection(int server_port) {
    struct sockaddr_in server_addr;
    /* Create socket */
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Client: Socket creation error \n");
        return false;
    }

    /* Define server address */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    /* Convert IPv4 and IPv6 addresses from text to binary form */
    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported \n");
        return false;
    }
    /* Connect to server */
    if (connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        std::cout << strerror(errno) << "\n";
        printf("Client: Connection Failed \n");
        return false;
    }

    return true;
}

/* Disconnects from server */
int client::close_connection() {
    return close(sock_fd);
}

/* Sends requests to server */
int client::send_request(request *req) {
    std::string req_msg = req->build_request_message();  // convert to http request message standard format
    std::cout << "Requesting with headers: " << std::endl;
    std::cout << req->get_header_as_string() << std::endl;
    std::cout << "===========================" << std::endl;
    return send(sock_fd, req_msg.c_str(), req_msg.length(), 0);// send request through connection socket
}

/*
 * This function is assigned to a dedicated receiver thread to ensure pipelining
 *  Handles all coming responses on the connection socket
 */
void client::process_response() {
    fd_set read_fds;
    struct timeval tv{};
    while (!this->is_last_request ||
           !this->requests_queue.empty()) { // keep working as long as more requests are to be handled
        /* Busy wait if expecting more requests but none has arrived yet */
        /* This occurs when a POST request was encountered and being processed, while subsequent requests were blocked */
        while (this->requests_queue.empty());

        /* Define 'select' parameters */
        FD_ZERO(&read_fds); // here we wait for data to arrive
        FD_SET(sock_fd, &read_fds);
        tv.tv_sec = 40;
        tv.tv_usec = 0;
        int activity = select(sock_fd + 1, &read_fds, NULL, NULL, &tv);

        /* Check 'select' return */
        if (activity < 0) {
            perror("Error while waiting to receive data");
            exit(EXIT_FAILURE);
        } else if (activity == 0) {
            std::cout << "Time Out, No More Responses Sent" << std::endl;
            exit(0);
        } else if (activity > 0 && FD_ISSET(sock_fd,
                                            &read_fds)) { // some data has arrived and needs to be read, or a change has occurred due to connection closing
            if (http_utils::is_closed(sock_fd)) { // check connection
                if (requests_queue.empty() && is_last_request) { // all requests were served completely
                    std::cout << "Success" << std::endl;
                } else {
                    std::cout << "Some requests were not served" << std::endl;
                }
                close_connection();
                break;
            }
            handle_responses(); // handle received responses while connected to server
        }
    }
    delete[] response_buffer;
}

/* Handles a response message received on socket */
void client::handle_responses() {
    ssize_t read_data_length = recv(sock_fd, response_buffer, MAX_BUFFER_SIZE, 0); // read socket buffer
    if (read_data_length <= 0) { // check errors
        perror("Error receiving response");
        exit(EXIT_FAILURE);
    }

    std::string buffer_string = std::string(response_buffer, read_data_length);
    std::vector<size_t> header_ends = http_utils::findHeaderEnds(
            buffer_string);// locate all header ends in case of multiple responses arrive on the same buffer
    if (header_ends.size() == 0) {
        perror("Headers max length exceeded");
        requests_queue.pop();
        return;
    }

    /* Process all received responses on the buffer */
    size_t prev_pos = 0;
    for (size_t headers_end_pos : header_ends) {
        curr_req = requests_queue.front();// retrieve the already-sent request corresponding to current response
        requests_queue.pop();

        std::string res_string = buffer_string.substr(prev_pos, headers_end_pos - prev_pos +
                                                                1); // obtain an individual complete response message
        response *res = new response();
        res->build_header(res_string);
        size_t body_start_pos = headers_end_pos + 4; // locate response body

        if (res->get_status() == response_status_code::CODE_200) {// take action on success only
            if (curr_req->get_method() == GET) {
                handle_get_response(curr_req, res, buffer_string, body_start_pos);
            } else {
                handle_post_request(curr_req);
            }
        }

        delete curr_req;
        delete res;

        prev_pos = body_start_pos + res->get_content_length(); // update pointer
    }
}

/* Handles responses to GET by saving the received data */
void client::handle_get_response(request *req, response *res, std::string res_string, int body_start_pos) {
    int body_len_in_res = std::min(res->get_content_length(), (int) (res_string.length() - body_start_pos));
    std::string body = res_string.substr(body_start_pos, body_len_in_res);
    int rem_len = res->get_content_length() - body.length();

    while (rem_len > 0) {
        ssize_t read_data_length = recv(sock_fd, response_buffer, std::min(rem_len, MAX_BUFFER_SIZE), 0);
        if (read_data_length <= 0) {
            perror("Error receiving data");
            exit(EXIT_FAILURE);
        }
        body += std::string(response_buffer, read_data_length);
        rem_len -= read_data_length;
    }
    res->set_body(body);

    writer.write(req->get_url(), res->get_body());
}

/* Handles POST requests by sending the intended data to server, after receiving 'OK' response */
void client::handle_post_request(request *req) {
    std::string file_data;
    file_reader reader;
    reader.read_file(req->get_url(), &file_data);
    //send post uploaded url through the socket to server
    send(sock_fd, file_data.c_str(), file_data.length(), 0);

    this->post_in_process = false;
}

/* Informs client that a POST request was encountered so that pipelining must hold */
void client::set_post_in_process() {
    this->post_in_process = true;
}

/* Tells the state of request queue if contains a POST request*/
bool client::is_post_in_process() {
    return this->post_in_process;
}

/* Adds a new request to queue*/
void client::push_request(request *req) {
    this->requests_queue.push(req);
}

/* Informs client that no further requests are expected */
void client::set_last_request() {
    this->is_last_request = true;
}
