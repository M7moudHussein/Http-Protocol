//
// Created by salma on 11/3/18.
//

#include "client.h"

client::client(std::queue<request *> requests) {
    client::requests = requests;
}

bool client::establish_connection(int server_port) {

    int sock = 0;
    struct sockaddr_in server_addr;
    //create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error \n");
        return false;
    }

    memset(&server_addr, '0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    //TODO take argument "127.0.0.1" from argument list sent instead of hardcoded
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported \n");
        return false;
    }
    //connect to server
    if (connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        printf("Connection Failed \n");
        return false;
    }

    return true;
}

void client::handle_get_reponse() {
//TODO implement GET response from server and saving received file
}

void client::handle_post_request() {
//TODO implement sending file for server on post request
}



