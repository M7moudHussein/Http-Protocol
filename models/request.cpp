#include <sstream>
#include <file_reader.h>
#include <iostream>
#include <iterator>
#include "request.h"

#define DEFAULT_PORT_NUMBER 80
#define DEFAULT_HTTP_VERSION HTTP_VERSION

request::request(std::string test_request) {
    std::stringstream ss(test_request);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> attributes(begin, end);
    this->method = attributes[0] == "GET" ? GET : POST;
    this->url = attributes[1];
    this->header_fields[HOST] = attributes[2];
    this->header_fields[CONNECTION] = KEEP_ALIVE;
    this->http_version = DEFAULT_HTTP_VERSION;

    /*optional port number given*/
    this->port_number = attributes.size() == 4 ? stoi(attributes[3]) : DEFAULT_PORT_NUMBER;

    if (this->method == POST) {
        file_reader reader;
        int file_size = reader.get_file_size(this->url);
        if (file_size < 0) {
            perror("Error getting file size");
            exit(EXIT_FAILURE);
        }
        this->header_fields[CONTENT_LENGTH] = std::to_string(file_size);
        this->header_fields[CONTENT_TYPE] = http_utils::get_content_type(this->url);
    }
}

request_method request::get_method() {
    return method;
}

std::string request::get_url() {
    return url;
}

int request::get_port_num() {
    return port_number;
}

long request::get_content_length() {
    return stoi(this->header_fields[CONTENT_LENGTH]);
}

std::string request::build_request_message() {
    std::string request_message;
    request_message = (method == GET ? "GET " : "POST ") + url + " " + http_version + CARRIAGE_RET + LINE_FEED;
    for (auto const &header_field : header_fields) {
        request_message += header_field.first + ": " + header_field.second + CARRIAGE_RET + LINE_FEED;
    }

    request_message = request_message + CARRIAGE_RET + LINE_FEED;
    request_message = request_message + body;
    return request_message;
}

std::string request::get_http_version() {
    return this->http_version;
}


void request::build_header(std::string header) {
    request_line = header.substr(0, header.find(CARRIAGE_RET));
    std::stringstream request_line_stream(request_line);

    std::string req_method;
    request_line_stream >> req_method >> url >> http_version;
    method = req_method == "GET" ? GET : POST;

    std::string header_lines = header.substr(header.find(LINE_FEED) + 1);
    std::stringstream headers_stream(header_lines);

    std::string header_field;
    while (getline(headers_stream, header_field)) {
        std::string key = header_field.substr(0, header_field.find(':'));
        std::string val = header_field.substr(header_field.find(": ") + 1);
        this->header_fields[key] = val;
    }
}

void request::build_body(std::string body) {
    this->body = body;
}