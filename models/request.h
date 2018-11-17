//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_REQUEST_H
#define HTTP_PROTOCOL_REQUEST_H

#include <string>

#define CARRIAGE_RET "\r"
#define LINE_FEED "\n"
#define HTTP_VERSION "1.0"
enum request_type {
    GET,
    POST
};

class request {
public:
    request() {};

    request(request_type type, std::string file_name, std::string host_name, int port_num);

    void set_type(request_type type);

    request_type get_type();

    void set_path(std::string file_name);

    std::string get_path();

    void set_host_name(std::string host_name);

    int get_port_num();

    int get_length();

    std::string get_host_name();

    std::string format();

    std::string get_http_version();

    void build(std::string req_msg);

private:
    request_type type;
    std::string file;
    std::string host;
    int port_number;
    std::string http_version;
    int post_content_len;
    std::string post_content_type;
};


#endif //HTTP_PROTOCOL_REQUEST_H
