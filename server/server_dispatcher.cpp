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

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int socket_no = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &address_len);
        if (socket_no < 0) {
            perror("accept");
            continue;
        }

        std::cout << "Connection created on socket: " << socket_no << std::endl;

        server_worker *worker = new server_worker(socket_no);
        worker->start();
    }
}

int server_dispatcher::init_server(struct sockaddr_in *address) {
    int server_fd;

    // Creating socket url descriptor
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
