//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_CLIENT_H
#define HTTP_PROTOCOL_CLIENT_H

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <response.h>
#include "queue"
#include "../models/request.h"
#include "../filehandler/file_reader.h"

class client {
public:
    client(std::string server_ip);

    bool establish_connection(int server_port);

    bool close_connection();

    int send_request(request *req);


private:
    std::string server_ip;
    int sock_fd = 0;
    /*in the case of GET*/
    void handle_get_reponse();

    /*in the case of POST*/
    void handle_post_request();
};


#endif //HTTP_PROTOCOL_CLIENT_H
