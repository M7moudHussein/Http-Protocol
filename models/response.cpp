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

void response::build(std::string res_msg) {
    // TODO: implement parsing
}

size_t response::get_length() {
    return strlen(to_string());
}

Status_code response::get_status() {
    return CODE_200;
}

void response::set_status(Status_code status_code) {
    this->status_code = status_code;
}

void response::set_body(char *response_body, int body_length) {
    this->response_body = response_body;
    this->body_length = body_length;
}

char *response::get_body() {
    return response_body;
}

int response::get_body_length() {
    return body_length;
}

void response::set_http_version(std::string http_version) {
    this->http_version = http_version;
}

std::string response::get_http_version() {
    return this->http_version;
}
