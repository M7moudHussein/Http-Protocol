//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_CLIENT_H
#define HTTP_PROTOCOL_CLIENT_H

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
class client {
public:
    bool establish_connection(int server_port);

    void send_request();

    void recieve_data();

    void send_data();
};


#endif //HTTP_PROTOCOL_CLIENT_H
