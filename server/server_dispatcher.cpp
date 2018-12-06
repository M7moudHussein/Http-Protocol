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
    struct sockaddr_in peer_address;
    int peer_addr_len = sizeof(peer_address);

    int server_fd = server_dispatcher::init_server(port_no);

    if (listen(server_fd, 10) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
        int socket_no = accept(server_fd, (struct sockaddr *) &peer_address, (socklen_t *) &peer_addr_len);
        if (socket_no < 0) {
            perror("accept");
            continue;
        }

        std::cout << "Connection created on socket: " << socket_no << std::endl;

        server_worker *worker = new server_worker(socket_no);
        worker->start();
    }
}

int server_dispatcher::init_server(int port_no) {
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port_no);
    int address_len = sizeof(server_address);
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
    if (bind(server_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}
