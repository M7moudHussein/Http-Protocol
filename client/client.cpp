//
// Created by salma on 11/3/18.
//

#include <cstring>
#include <arpa/inet.h>
#include "client.h"

bool client::establish_connection(int server_port) {

    int sock = 0;
    struct sockaddr_in server_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error \n");
        return false;
    }

    memset(&server_addr, '0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported \n");
        return false;
    }

    if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        printf("Connection Failed \n");
        return false;
    }

    return true;
}

void client::send_request() {

}

void client::recieve_data() {

}

void client::send_data() {

}
