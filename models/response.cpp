#include <cstring>
#include <iostream>
#include <sstream>
#include "response.h"

response::response() {

}

std::string response::build_response_message() {
    std::string response_message = this->http_version + " " + get_status_string() + CARRIAGE_RET + LINE_FEED;

    for (auto const &header_field : header_fields) {
        response_message += header_field.first + ": " + header_field.second + CARRIAGE_RET + LINE_FEED;
    }
    response_message = response_message + CARRIAGE_RET + LINE_FEED;
    response_message += body;
    return response_message;
}

response_status_code response::get_status() {
    return this->status_code;
}

void response::set_status(response_status_code status_code) {
    this->status_code = status_code;
}

void response::set_body(std::string body) {
    this->body = body;
}

std::string response::get_body() {
    return body;
}

void response::set_http_version(std::string http_version) {
    this->http_version = http_version;
}


void response::set_content_type(std::string content_type) {
    this->header_fields[CONTENT_TYPE] = content_type;
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

void response::set_content_length(int content_length) {
    this->header_fields[CONTENT_LENGTH] = std::to_string(content_length);
}


void response::build_header(std::string header) {
    std::string status_line = header.substr(0, header.find(CARRIAGE_RET));
    std::stringstream request_line_stream(status_line);

    std::string status;
    request_line_stream >> http_version >> status;

    status_code = status == "200" ? CODE_200 : CODE_404;

    std::string header_lines = header.substr(header.find(LINE_FEED) + 1);
    std::stringstream headers_stream(header_lines);

    std::string header_field;
    while (getline(headers_stream, header_field)) {
        std::string key = header_field.substr(0, header_field.find(':'));
        std::string val = header_field.substr(header_field.find(": ") + 2)
                .substr(0, header_field.rfind(CARRIAGE_RET));
        this->header_fields[key] = val;
    }
}

int response::get_content_length() {
    return stoi(header_fields[CONTENT_LENGTH]);
}
