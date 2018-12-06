#ifndef HTTP_PROTOCOL_SERVER_DISPATCHER_H
#define HTTP_PROTOCOL_SERVER_DISPATCHER_H

#include "server_worker.h"
#include "../models/request.h"

class server_dispatcher {
public :
    /* runs the server on a certain port number where:
     * 1. server is initiated and TCP socket created.
     * 2. server listens for connections from clients.
     * 3. server accepts connection from a client.
     * 4. a server worker thread is created to serve the requests of each client */
    static void run_server(int port_no);

private:
    /* creates a TCP socket for the server and attaches this socket
    * to a certain port given the socket address */
    static int init_server(int i);
};

#endif //HTTP_PROTOCOL_SERVER_DISPATCHER_H
