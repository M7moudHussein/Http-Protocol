//
// Created by salma on 11/3/18.
//

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
    std::string req="";
    req += ((type == GET) ? "GET" : "POST") + file + "HTTP/"+ HTTP_VERSION + CARRIAGE_RET + LINE_FEED;
    req += "Host: " + host + CARRIAGE_RET + LINE_FEED;
    req += CARRIAGE_RET;
    req += LINE_FEED;
    //TODO add "KEEP ALIVE"
    return req;
}
