//
// Created by salma on 11/3/18.
//

#include "client.h"

client::client(std::string server_ip) {
    client::server_ip = server_ip;
}

bool client::establish_connection(int server_port) {
    struct sockaddr_in server_addr;
    //create socket
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error \n");
        return false;
    }

    memset(&server_addr, '0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported \n");
        return false;
    }
    //connect to server
    if (connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
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

int client::send_request(request *req) {
    std::string req_msg = req->format();
    return send(sock_fd,req_msg.c_str(), req_msg.length(), 0);
}



