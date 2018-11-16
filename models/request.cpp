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

void request::set_port_num(int port_num) {
    request::port_number = port_num;
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

void request::build(std::string req_msg) {
    std::stringstream stream, first_line, second_line;
    std::string temp_buffer;
    stream << req_msg;

    getline(stream, temp_buffer);
    first_line << temp_buffer;

    getline(stream, temp_buffer);
    second_line << temp_buffer;

    std::string request_type, path, protocol_version;
    first_line >> request_type >> path >> protocol_version;

    std::string host_name, port_number;
    second_line >> temp_buffer >> temp_buffer;

    unsigned long colon_index = temp_buffer.find(':');
    host_name = temp_buffer.substr(0, colon_index + 1);
    port_number = temp_buffer.substr(colon_index + 1);

    request::type = request_type == "POST" ? POST : GET;
    request::file = path;
    request::host = host_name;
    request::port_number = stoi(port_number);
}


