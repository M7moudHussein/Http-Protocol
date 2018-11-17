//
// Created by salma on 11/3/18.
//

#include <cstring>
#include <iostream>
#include <sstream>
#include "response.h"

std::string response::format() {
    std::string header_line_1 =
            "HTTP/" + http_version + " " + get_status_string() + CARRIAGE_RETURN + NEW_LINE;
    std::string response_string = header_line_1;
    if (this->req_type == GET) {
        std::string header_line_2 =
                "Content-Length: " + std::to_string(response_body.length()) + CARRIAGE_RETURN + NEW_LINE;
        std::string header_line_3 = "Content-Type: " + content_type + CARRIAGE_RETURN + NEW_LINE;

        response_string = response_string + header_line_2 + header_line_3;
    }
    response_string = response_string + CARRIAGE_RETURN + NEW_LINE + response_body;
    response_length = response_string.length();
    return response_string;
}

void response::build(std::string res_msg) {
    std::stringstream stream, first_line;
    std::string temp_buffer;

    getline(stream, temp_buffer);
    first_line << temp_buffer;

    std::string http_string, response_status_code;
    first_line >> http_string >> response_status_code;

    this->http_version = http_string.substr(http_string.find("/") + 1);
    this->response_status_code = response_status_code == "200" ? CODE_200 : CODE_404;

    if (this->req_type == GET) {
        std::stringstream second_line, third_line;
        getline(stream, temp_buffer);
        second_line << temp_buffer;

        getline(stream, temp_buffer);
        third_line << temp_buffer;

        std::string content_length;
        second_line >> temp_buffer >> content_length;

        std::string content_type;
        third_line >> temp_buffer >> content_type;

        getline(stream, temp_buffer); // skip empty line between header and body
        std::string response_body = temp_buffer;

        this->content_type = content_type;
        this->response_body = response_body;
    }
}

int response::get_length() {
    return response_length;
}

status_code response::get_status() {
    return CODE_200;
}

void response::set_status(status_code status_code) {
    this->response_status_code = status_code;
}

void response::set_body(std::string response_body) {
    this->response_body = response_body;
}

std::string response::get_body() {
    return response_body;
}

int response::get_body_length() {
    return response_body.length();
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
    switch (response_status_code) {
        case CODE_200:
            return "200 OK";
        case CODE_404:
            return "404 NOT FOUND";
        default:
            exit(EXIT_FAILURE);
    }
}

void response::set_request_type(request_type req_type) {
    this->req_type = req_type;
}