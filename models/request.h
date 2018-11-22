#ifndef HTTP_PROTOCOL_REQUEST_H
#define HTTP_PROTOCOL_REQUEST_H

#include <string>
#include <map>
#include "http_utils.h"

class request {
public:
    request() = default;

    request(std::string test_request);

    request_method get_method();

    std::string get_url();

    int get_port_num();

    long get_content_length();

    std::string build_request_message();

    std::string get_http_version();

    void build_header(std::string header);

    void build_body(std::string body);

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
