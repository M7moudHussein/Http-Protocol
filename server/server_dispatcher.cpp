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
        if (listen(server_fd, 10) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }

        int socket_no = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &address_len);
        if (socket_no < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        server_worker *worker = process_request(socket_no);
        worker->process_request();
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
        server_worker *worker = new server_worker(req, socket_no);
        return worker;
    }
    //TODO Add else
    return nullptr;
}

request *server_dispatcher::parse_request(char *buffer) {
    request *req = new request();
    std::string request_msg = std::string(buffer);
    req->build(request_msg);
    return req;
}
