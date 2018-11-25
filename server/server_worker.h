#ifndef HTTP_PROTOCOL_SERVER_WORKER_H
#define HTTP_PROTOCOL_SERVER_WORKER_H


#include "request.h"
#include "response.h"
#include <queue>
#include <file_writer.h>

// https://stackoverflow.com/questions/686217/maximum-on-http-header-values
#define REQUEST_BUFFER_SIZE 8192

/*server worker is responsible for handling requests of a certain client*/
class server_worker {
public:
    server_worker(int socket_no);

    void start();

private:
    char request_buffer[REQUEST_BUFFER_SIZE];
    /* boolean indicating a post request is cached in order to stop pipeline */
    bool post_in_queue;
    bool has_timed_out;
    /* queue for caching requests sent from client */
    std::queue<request *> requests_queue;
    int socket_fd;

    /*A thread handles retrieving requests from the TCP socket buffer
 * to avoid being filled and therfore blocking the client*/
    void retrieve_requests();

    response *handle_get_request(request *request_to_process);

    response *handle_post_request(request *request_to_process);

    void handle_post_followers(request *request_to_process);

    /* reads received requests on the TCP socket and caches them in main memory */
    void pull_requests();

    /* send responses for the received requests whether they are GET or POST */
    void process_requests();
};

#endif //HTTP_PROTOCOL_SERVER_WORKER_H
