#ifndef HTTP_PROTOCOL_REQUEST_H
#define HTTP_PROTOCOL_REQUEST_H

#include <string>
#include <map>
#include "http_utils.h"

class request {
public:
    request() = default;

    request(std::string test_request);

    /* get type of request : GET or POST */
    request_method get_method();

    std::string get_url();

    long get_content_length();

    /* builds the request message to be sent to the server */
    std::string build_request_message();

    std::string get_header_as_string();

    /* determines http version: 1.0 or 1.1 */
    std::string get_http_version();

    /* build the header fields of a request */
    void build_header(std::string header);

private:
    std::string request_line;
    std::string header;
    request_method method;
    std::string url;
    std::string http_version;
    std::map<std::string, std::string> header_fields;
    std::string host;
    int port_number;
    std::string body;
};


#endif //HTTP_PROTOCOL_REQUEST_H
