//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_SERVER_WORKER_H
#define HTTP_PROTOCOL_SERVER_WORKER_H


#include "request.h"
#include "response.h"
#include "response_sender.h"

class server_worker {
public:
    server_worker(request *req);

    void process_request(response_sender *sender);

private:
    request *request_to_process;
};

#endif //HTTP_PROTOCOL_SERVER_WORKER_H
