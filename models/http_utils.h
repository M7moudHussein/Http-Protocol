#ifndef HTTP_PROTOCOL_HTTP_UTILS_H
#define HTTP_PROTOCOL_HTTP_UTILS_H

#include <string>
#include <vector>

#define HOST "Host"
#define CONTENT_LENGTH "Content-Length"
#define CONTENT_TYPE "Content-Type"
#define CONNECTION "Connection"
#define KEEP_ALIVE "keep-alive"
#define HTTP_VERSION "HTTP/1.1"
#define CARRIAGE_RET "\r"
#define LINE_FEED "\n"
#define HEADERS_END "\r\n\r\n"

class request;

enum request_method {
    GET,
    POST
};

enum response_status_code {
    CODE_404,
    CODE_200
};

class http_utils {
public:
    static std::string get_content_type(std::string url);
    static std::vector<size_t > findHeaderEnds(std::string recieved_buffer);
};


#endif
