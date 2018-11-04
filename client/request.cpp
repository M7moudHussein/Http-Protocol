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

std::string request::get_file_name() {
    return file;
}

int request::get_port_num() {
    return port_number;
}

std::string request::get_host_name() {
    return host;
}
