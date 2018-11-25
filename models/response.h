#ifndef HTTP_PROTOCOL_RESPONSE_H
#define HTTP_PROTOCOL_RESPONSE_H

#include <string>
#include <map>
#include "http_utils.h"

class response {
public:
    response();

    /* set status code for response: 200 OK or 404 Not Found */
    void set_status(response_status_code code);

    response_status_code get_status();

    std::string get_status_string();

    /* build the response message to be sent to the client */
    std::string build_response_message();

    std::string get_headers_as_string();

    void set_body(std::string body);

    std::string get_body();

    void set_http_version(std::string http_version);

    /* sets the type of the file content : txt, html, image */
    void set_content_type(std::string content_type);

    /*sets the length of the content sent in the body of the response */
    void set_content_length(int content_length);

    void build_header(std::string header_string);

    int get_content_length();

private:
    response_status_code status_code;
    std::map<std::string, std::string> header_fields;
    std::string body;
    std::string http_version;
};


#endif
