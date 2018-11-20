//
// Created by mahmoud on 11/20/18.
//

#ifndef HTTP_PROTOCOL_HTTP_UTILS_H
#define HTTP_PROTOCOL_HTTP_UTILS_H

#include <string>

#define HOST "Host"
#define CONTENT_LENGTH "Content-Length"
#define CONTENT_TYPE "Content-Type"
#define KEEP_ALIVE "Keep-Alive"
#define HTTP_VERSION_1_0 "HTTP/1.0"
#define HTTP_VERSION_1_1 "HTTP/1.1"
#define CARRIAGE_RET "\r"
#define LINE_FEED "\n"

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
};


#endif //HTTP_PROTOCOL_HTTP_UTILS_H
