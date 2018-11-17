//
// Created by salma on 11/3/18.
//

#include <sstream>
#include <file_reader.h>
#include <iostream>
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
    std::cout << "format\n";
    std::string req = "";
    req += ((type == GET) ? "GET" : "POST") + ' ' + file + ' ' + "HTTP/" + HTTP_VERSION + CARRIAGE_RET + LINE_FEED;
    req += "Host: " + host + CARRIAGE_RET + LINE_FEED;
    if (type == POST) {
        std::cout << "request = post\n";
        //get file length for post request and get content type
        FILE *p_file = NULL;
        p_file = fopen(file.c_str(), "rb");
        fseek(p_file, 0, SEEK_END);
        post_content_len = ftell(p_file);
        fclose(p_file);
        if (post_content_len == -1) {
            //TODO send 404 from server side
        } else {
            std::cout << "calculating length\n";
            std::string extension;
            for (int i = file.length() - 1; i >= 0; i--) {
                std::cout << i << "\n";
                if (file[i] == '.') {
                    extension = file.substr(i + 1);
                    std::cout << "extension detected\n";
                }
            }

            if (extension == "txt") {
                post_content_type = "text/plain";
            } else if (extension == "html") {
                post_content_type = "text/html";
            } else {
                post_content_type = "image" + std::string("/") + extension;
            }
        }
        req += "Content-Length: " + std::to_string(post_content_len) + CARRIAGE_RET + LINE_FEED;
        req += "Content-Type: " + post_content_type + CARRIAGE_RET + LINE_FEED;
    }
    req += CARRIAGE_RET;
    req += LINE_FEED;
    //TODO add "KEEP ALIVE"
    return req;
}

std::string request::get_http_version() {
    return this->http_version;
}

void request::build(std::string req_msg) {
    std::stringstream stream, first_line, second_line, third_line;
    std::string temp_buffer, post_content_len_line, post_content_line;
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

    if (type == POST) {
        second_line << temp_buffer;
        getline(stream, temp_buffer);
        second_line >> post_content_len_line;
        std::cout<<post_content_len_line<<"\n";
        request::post_content_len = stoi(post_content_len_line.substr(post_content_len_line.find(":") + 1));
        third_line << temp_buffer;
        third_line >> post_content_line;
        std::cout<<post_content_line<<"\n";
        request::post_content_type = post_content_line.substr(post_content_line.find(":") + 1);
    }

}

int request::get_length() {
    return request::post_content_len;
}

