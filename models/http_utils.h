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

/* request types */
enum request_method {
    GET,
    POST
};

/* response codes ---> 200 represents OK ... and 404 represents Not Found */
enum response_status_code {
    CODE_404,
    CODE_200
};

/* utility functions used by the server and the client */
class http_utils {
public:
    /* retrieve the type of the file whether it is txt, html, image */
    static std::string get_content_type(std::string url);

    /* finds the positions of header ends to split requests */
    static std::vector<size_t> findHeaderEnds(std::string received_buffer);

    /* check if a socket got closed */
    static bool is_closed(int socket_fd);
};


#endif
