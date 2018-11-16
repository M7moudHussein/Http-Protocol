//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_RESPONSE_H
#define HTTP_PROTOCOL_RESPONSE_H


#include <string>
#include <magic.h>

enum Status_code {
    CODE_404,
    CODE_200
};

class response {
public:
    void set_status(Status_code code);

    Status_code get_status();

    std::string get_status_string();

    char *to_string();

    size_t get_length();

    void set_body(char *body, int body_length);

    void set_http_version(std::string http_version);

    std::string get_http_version();

    void set_content_type(const char *string);

private:
    static const char CARRIAGE_RETURN = '\r';
    static const char NEW_LINE = '\n';


    Status_code status_code;
    char *response_body;
    int body_length;
    std::string http_version;
    std::string content_type;
};


#endif //HTTP_PROTOCOL_RESPONSE_H
