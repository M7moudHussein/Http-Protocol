#ifndef HTTP_PROTOCOL_SERVER_DISPATCHER_H
#define HTTP_PROTOCOL_SERVER_DISPATCHER_H

#include "server_worker.h"
#include "../models/request.h"

class server_dispatcher {
public :
    static void run_server(int port_no);

private:
    static int init_server(struct sockaddr_in *address);
};

#endif //HTTP_PROTOCOL_SERVER_DISPATCHER_H
