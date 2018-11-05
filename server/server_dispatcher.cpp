#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <sstream>
#include "server_dispatcher.h"

void server_dispatcher::run_server(int port_no) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_no);
    int address_len = sizeof(address);

    int server_fd = server_dispatcher::init_server(&address);

    while (true) {
        if (listen(server_fd, 1) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        int socket_no = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &address_len);
        if (socket_no < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        process_request(socket_no);
    }
}

int server_dispatcher::init_server(struct sockaddr_in *address) {
    int server_fd;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *) address, sizeof(*address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

server_worker *server_dispatcher::process_request(int socket_no) {
    char *buffer = new char[REQUEST_BUFFER_SIZE];
    ssize_t data_len = read(socket_no, buffer, REQUEST_BUFFER_SIZE);
    if (data_len > -1) {
        request *req = server_dispatcher::parse_request(buffer);
        delete[] buffer;
        server_worker *worker = new server_worker(req);
        delete req;
        return worker;
    }
    //TODO Add else
    return nullptr;
}

request *server_dispatcher::parse_request(char *buffer) {
    std::stringstream ss, first_line, second_line;
    std::string temp_buffer;
    std::cout << buffer << std::endl;
    ss << buffer;

    getline(ss, temp_buffer);
    first_line << temp_buffer;

    getline(ss, temp_buffer);
    second_line << temp_buffer;

    std::string request_type, path, protocol_version;
    first_line >> request_type >> path >> protocol_version;

    std::string host_name, port_number;
    second_line >> temp_buffer >> temp_buffer;

    unsigned long colon_index = temp_buffer.find(':');
    host_name = temp_buffer.substr(0, colon_index + 1);
    port_number = temp_buffer.substr(colon_index + 1);

    request *req = new request();
    req->set_type(request_type == "POST" ? POST : GET);
    req->set_path(path);
    req->set_host_name(host_name);
    req->set_port_num(stoi(port_number));
    return req;
}
