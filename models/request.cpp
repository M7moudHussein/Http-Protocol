//
// Created by salma on 11/3/18.
//

#include <sstream>
#include "request.h"

request::request(request_type r_type, std::string file_name, std::string host_name, int port_num) {
    type = r_type;
    file = file_name;
    host = host_name;
    port_number = port_num;
}

request_type request::get_type() {
    return type;
}

std::string request::get_path() {
    return file;
}

int request::get_port_num() {
    return port_number;
}

std::string request::get_host_name() {
    return host;
}

void request::set_type(request_type type) {
    request::type = type;
}

void request::set_path(std::string file_name) {
    request::file = file_name;

}

void request::set_host_name(std::string host_name) {
    request::host = host_name;

}

std::string request::format() {
    std::string req = "";
    req += ((type == GET) ? "GET" : "POST") + file + "HTTP/" + HTTP_VERSION + CARRIAGE_RET + LINE_FEED;
    req += "Host: " + host + CARRIAGE_RET + LINE_FEED;
    req += CARRIAGE_RET;
    req += LINE_FEED;
    //TODO add "KEEP ALIVE"
    return req;
}

std::string request::get_http_version() {
    return this->http_version;
}

void request::build(std::string req_msg) {
    std::stringstream stream, first_line;
    std::string temp_buffer;
    stream << req_msg;

    getline(stream, temp_buffer);
    first_line << temp_buffer;

    getline(stream, temp_buffer);

    std::string request_type, path, protocol_version;
    first_line >> request_type >> path >> protocol_version;
    path = path.substr(1);

    request::type = request_type == "POST" ? POST : GET;
    request::file = path;
    request::http_version = protocol_version.substr(protocol_version.find('/') + 1);
}
