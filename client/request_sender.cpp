//
// Created by salma on 11/8/18.
//

#include "request_sender.h"

request_sender::request_sender(int socket_no) {
    //TODO chech if param should be socket number or server ip address
    request_sender::socket_no = socket_no;
}

void request_sender::send_request(request *req) {
    //TODO first build the request then send it to the server
    //build_request();
}

char *request_sender::build_request(request *req) {
    //TODO implement constructing request in HTTP format
    return nullptr;
}
