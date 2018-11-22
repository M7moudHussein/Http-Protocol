#ifndef HTTP_PROTOCOL_HTTP_UTILS_H
#define HTTP_PROTOCOL_HTTP_UTILS_H

#include <string>

#define HOST "Host"
#define CONTENT_LENGTH "Content-Length"
#define CONTENT_TYPE "Content-Type"
#define CONNECTION "Connection"
#define KEEP_ALIVE "Keep-Alive"
#define HTTP_VERSION "HTTP/1.1"
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

class http_utils {
public:
    static std::string get_content_type(std::string url);
};


#endif
