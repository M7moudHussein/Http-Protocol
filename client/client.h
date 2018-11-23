#ifndef HTTP_PROTOCOL_CLIENT_H
#define HTTP_PROTOCOL_CLIENT_H
#define MAX_BUFFER_SIZE 1 << 13

#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <response.h>
#include <file_writer.h>
#include <request.h>

class client {
public:
    client(std::string server_ip);

    void start();

    bool establish_connection(int server_port);

    int close_connection();

    int send_request(request *req);

    void handle_get_response(request *, response *);

    void handle_post_request(request *);

    void process_response();

    void set_current_request(request *current_request);
    std::thread *receiver_thread;

private:
    int sock_fd = 0;
    std::string server_ip;
    file_writer writer;
    request *curr_req;
};

#endif
