#ifndef HTTP_PROTOCOL_CLIENT_H
#define HTTP_PROTOCOL_CLIENT_H
#define MAX_BUFFER_SIZE 8192

#include <sys/socket.h>
#include <thread>
#include <netinet/in.h>
#include <cstring>
#include <arpa/inet.h>
#include <queue>
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

    void handle_get_response(request *, response *, std::string string, int body_start_pos);

    void handle_post_request(request *);

    void process_response();

    std::thread *receiver_thread;

    void set_post_in_process();

    bool is_post_in_process();

    void push_request(request *req);

    void set_last_request();

private:
    char *response_buffer;
    int sock_fd = 0;
    std::string server_ip;
    file_writer writer;
    request *curr_req;
    std::queue<request *> requests_queue;
    bool post_in_process;
    bool is_last_request;

    void handle_responses();
};

#endif
