#ifndef HTTP_PROTOCOL_RESPONSE_H
#define HTTP_PROTOCOL_RESPONSE_H

#include <string>
#include <map>
#include "http_utils.h"

class response {
public:
    void set_status(response_status_code code);

    response_status_code get_status();

    std::string get_status_string();

    std::string build_response_message();

    void build(std::string res_msg);

    void set_body(std::string body);

    std::string get_body();

    int get_body_length();

    void set_http_version(std::string http_version);

    void set_content_type(std::string content_type);

    void set_content_length(int content_length);

private:
    response_status_code status_code;
    std::map<std::string, std::string> header_fields;
    std::string body;
    std::string http_version;
};


#endif
