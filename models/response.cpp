//
// Created by salma on 11/3/18.
//

#include <cstring>
#include "response.h"

char *response::to_string() {
    char *reply =
            const_cast<char *>("HTTP/1.1 200 OK\n"
                               "Content-Length: 15\n"
                               "\n"
                               "sdfkjsdnbfkjbsf");
    return reply;
}

size_t response::get_length() {
    return strlen(to_string());
}
