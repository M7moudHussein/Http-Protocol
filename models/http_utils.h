//
// Created by mahmoud on 11/20/18.
//

#ifndef HTTP_PROTOCOL_HTTP_UTILS_H
#define HTTP_PROTOCOL_HTTP_UTILS_H

#include <string>
//#include "request.h"

#define HOST "Host"
#define CONTENT_LENGTH "Content-Length"
#define CONTENT_TYPE "Content-Type"
#define CONNECTION "Connection"
#define KEEP_ALIVE "Keep-Alive"
#define HTTP_VERSION_1_0 "HTTP/1.0"
#define HTTP_VERSION_1_1 "HTTP/1.1"
#define CARRIAGE_RET "\r"
#define LINE_FEED "\n"

class request;

enum request_method {
    GET,
    POST
};

enum response_status_code {
    CODE_404,
    CODE_200
};

struct thread_args {
    int socket_no;
    request *request_to_process;

    thread_args(int socket_no, request *request_to_process) {
        this->socket_no = socket_no;
        this->request_to_process = request_to_process;
    }
};

struct receiver_args {
    int socket_fd;
    receiver_args(int socket_fd) {
        this->socket_fd = socket_fd;
    }
};

class http_utils {
public:
    static std::string get_content_type(std::string url);
};


#endif //HTTP_PROTOCOL_HTTP_UTILS_H
