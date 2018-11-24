#ifndef HTTP_PROTOCOL_SERVER_WORKER_H
#define HTTP_PROTOCOL_SERVER_WORKER_H


#include "request.h"
#include "response.h"
#include <queue>
#include <file_writer.h>

// https://stackoverflow.com/questions/686217/maximum-on-http-header-values
#define REQUEST_BUFFER_SIZE 1 << 13

class server_worker {
public:
    server_worker(int socket_no);

    void start();

private:
    char request_buffer[REQUEST_BUFFER_SIZE];
    bool post_in_queue;
    bool has_timed_out;
    std::queue<request *> requests_queue;
    int socket_fd;

    void retrieve_requests();

    response *handle_get_request(request *request_to_process);

    response *handle_post_request(request *request_to_process);

    void handle_post_followers(request *request_to_process);

    void pull_requests();

    void process_requests();
};

#endif //HTTP_PROTOCOL_SERVER_WORKER_H
