#include <file_reader.h>
#include <iostream>
#include "client.h"

client::client(std::string server_ip) {
    client::server_ip = server_ip;
}

void client::start() {
    receiver_thread = new std::thread(&client::process_response, this);
}

void client::set_current_request(request *current_request) {
    this->curr_req = current_request;
}

bool client::establish_connection(int server_port) {
    struct sockaddr_in server_addr;
    // Create socket
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Client: Socket creation error \n");
        return false;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported \n");
        return false;
    }
    // Connect to server
    if (connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        std::cout << strerror(errno) << "\n";
        printf("Client: Connection Failed \n");
        return false;
    }

    return true;
}

bool client::close_connection() {
    return false;
}

int client::send_request(request *req) {
    std::string req_msg = req->build_request_message();
    std::cout << req_msg << std::endl;
    return send(sock_fd, req_msg.c_str(), req_msg.length(), 0);
}

void client::process_response() {
    char *response_buffer = new char[MAX_BUFFER_SIZE];
    fd_set read_fds;
    struct timeval tv{};
    while (true) {
        std::cout<<"RRRRR";
        FD_ZERO(&read_fds);
        FD_SET(sock_fd, &read_fds);
        tv.tv_sec = 5;
        tv.tv_usec = 0;
        int activity = select(sock_fd + 1, &read_fds, NULL, NULL, &tv);
        std::cout<<activity;
        if (activity < 0) {
            perror("Error while waiting to receive data");
            exit(EXIT_FAILURE);
        } else if (activity == 0) {
            std::cout << "Time Out, No More Responses Sent" << std::endl;
            exit(0);
        } else if (activity > 0 && FD_ISSET(sock_fd, &read_fds)) {
            ssize_t read_data_length = recv(sock_fd, response_buffer, MAX_BUFFER_SIZE, 0);
            if (read_data_length > 0) {
                response *res = new response();
                res->build(std::string(response_buffer, read_data_length));
                if (res->get_status() == response_status_code::CODE_200) {
                    if (curr_req->get_method() == GET) {
                        handle_get_response(curr_req, res);
                    } else {
                        handle_post_request(curr_req);
                    }
                } else {
                    // TODO HANDLE 'NOT FOUND' ERROR
                }
                delete res;
            } else {
                break;
                // TODO HANDLE RECEIVING ERRORS
            }

            delete[] response_buffer;
        }
    }
}


void client::handle_get_response(request *req, response *res) {
    std::cout<<"HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
    writer.write(req->get_url(), res->get_body());
}

void client::handle_post_request(request *req) {
    std::string file_data;
    file_reader reader;
    reader.read_file(req->get_url(), &file_data);
    //send post uploaded url through the socket to server
    //TODO handle chunks
    send(sock_fd, file_data.c_str(), file_data.length(), 0);
}