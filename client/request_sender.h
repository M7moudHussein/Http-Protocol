//
// Created by salma on 11/8/18.
//

#ifndef HTTP_PROTOCOL_REQUEST_SENDER_H
#define HTTP_PROTOCOL_REQUEST_SENDER_H


#include "../models/request.h"

class request_sender {
public:
    request_sender(int socket_no);

    void send_request(request *req);

private:
    int socket_no;

    /*build request in the http format that the server can interpret* ... headers, body and stuff*/
    char *build_request(request *req);
};


#endif //HTTP_PROTOCOL_REQUEST_SENDER_H
