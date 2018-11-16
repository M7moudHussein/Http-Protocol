//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_SERVER_WORKER_H
#define HTTP_PROTOCOL_SERVER_WORKER_H


#include "request.h"
#include "response.h"
#include <sys/socket.h>

class server_worker {
public:
    server_worker(request *req, int socket_no);

    void process_request();

private:
    request *request_to_process;
    int socket_no;
};

#endif //HTTP_PROTOCOL_SERVER_WORKER_H
