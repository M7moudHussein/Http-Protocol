//
// Created by salma on 11/3/18.
//

#include <cstring>
#include "response.h"

char *response::to_string() {
    std::string response_line_1 = "HTTP/" + http_version + " " + get_status_string() + "\r\n";
    std::string response_line_2 = "Content-Length: " + std::to_string(body_length) + "\r\n";
    std::string response_line_3 = "Content-Type: " + content_type;
    std::string response_line_4 = "\r\n";
    std::string response_line_5 = response_body;
    return const_cast<char *>((response_line_1 + response_line_2 + response_line_3 + response_line_4 +
                               response_line_5).c_str());
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

void response::set_http_version(std::string http_version) {
    this->http_version = http_version;
}

std::string response::get_http_version() {
    return this->http_version;
}

void response::set_content_type(const char *content_type) {
    this->content_type = std::string(content_type);
}

std::string response::get_status_string() {
    switch (status_code) {
        case CODE_200:
            return "200 OK";
        case CODE_404:
            return "404 NOT FOUND";
        default:
            exit(EXIT_FAILURE);
    }
}
