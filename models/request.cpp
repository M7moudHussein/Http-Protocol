#include <sstream>
#include <file_reader.h>
#include "request.h"

#define DEFAULT_PORT_NUMBER 80
#define DEFAULT_HTTP_VERSION HTTP_VERSION_1_0

request::request(std::string test_request) {
    std::vector<std::string> attributes;
    std::stringstream line_stream(test_request);
    std::string temp_buffer;

    while (getline(line_stream, temp_buffer, ' ')) {
        attributes.push_back(temp_buffer);
    }

    this->method = attributes[0] == "GET" ? GET : POST;
    this->url = attributes[1];
    this->header_fields[HOST] = attributes[2];
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

long request::get_body_length() {
    return this->body.length();
}

std::string request::build_request_message() {
    std::string request_message;
    request_message = (method == GET ? "GET " : "POST ") + url + " " + http_version + CARRIAGE_RET + LINE_FEED;
    for (auto const &header_field : header_fields) {
        request_message += header_field.first + ": " + header_field.second + CARRIAGE_RET + LINE_FEED;
    }

    request_message = request_message + CARRIAGE_RET + LINE_FEED;
    request_message = request_message + body;
    //TODO add "KEEP ALIVE"
    return request_message;
}

std::string request::get_http_version() {
    return this->http_version;
}

void request::build(std::string req_msg) {
    std::string request_line = req_msg.substr(0, req_msg.find(CARRIAGE_RET));
    std::stringstream request_line_stream(request_line);

    std::string req_method;
    request_line_stream >> req_method >> url >> http_version;
    method = req_method == "GET" ? GET : POST;

    std::string headers_end;
    headers_end = headers_end + CARRIAGE_RET + LINE_FEED + CARRIAGE_RET + LINE_FEED;
    std::string headers = req_msg.substr(req_msg.find(LINE_FEED) + 1, req_msg.rfind(headers_end));
    std::stringstream headers_stream(headers);

    std::string header_field;
    while (getline(headers_stream, header_field)) {
        std::string key = header_field.substr(0, header_field.find(':'));
        std::string val = header_field.substr(header_field.find(": ") + 1);
        this->header_fields[key] = val;
    }
    this->body = req_msg.substr(req_msg.find(headers_end) + headers_end.length());
}