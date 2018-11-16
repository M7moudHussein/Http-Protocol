//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_RESPONSE_H
#define HTTP_PROTOCOL_RESPONSE_H


#include <string>

class response {
public:
    static response RESPONSE_200;
    static response RESPONSE_404;

    response();

    char *to_string();

    size_t get_length();

private:
    static const char CARRIAGE_RETURN = '\r';
    static const char NEW_LINE = '\n';
};


#endif //HTTP_PROTOCOL_RESPONSE_H
