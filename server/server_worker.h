#ifndef HTTP_PROTOCOL_SERVER_WORKER_H
#define HTTP_PROTOCOL_SERVER_WORKER_H


#include "request.h"
#include "response.h"
#include <sys/socket.h>
#include <file_writer.h>

class server_worker {
public:
    server_worker(request req, int socket_no);

    void process_request();

private:
    request request_to_process;
    int socket_no;
};

#endif //HTTP_PROTOCOL_SERVER_WORKER_H
