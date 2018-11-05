//
// Created by mahmoud on 11/3/18.
//

#ifndef HTTP_PROTOCOL_SERVER_DISPATCHER_H
#define HTTP_PROTOCOL_SERVER_DISPATCHER_H

#include "server_worker.h"
#include "../models/request.h"

//https://stackoverflow.com/questions/2811006/what-is-a-good-buffer-size-for-socket-programming
#define REQUEST_BUFFER_SIZE 1 << 13

class server_dispatcher {
public :
    static void run_server(int port_no);

private:
    static int init_server(struct sockaddr_in *address);

    static server_worker *process_request(int socket_no);

    static request *parse_request(char *buffer);
};

#endif //HTTP_PROTOCOL_SERVER_DISPATCHER_H
