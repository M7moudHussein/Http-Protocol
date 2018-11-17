//
// Created by salma on 11/3/18.
//

#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include "file_reader.h"

#define DEFAULT_PORT 80

std::queue<request *> file_reader::parse_requests(std::string request_file) {
    std::queue<request *> requests;
    std::ifstream infile(request_file);
    std::string line;
    while (std::getline(infile, line)) {
        std::vector<std::string> attributes;
        std::stringstream check1(line);
        std::string intermediate;
        while (getline(check1, intermediate, ' ')) {
            attributes.push_back(intermediate);
        }
        request *r;
        request_type type;
        if (attributes[0] == "GET")
            type = request_type::GET;
        else
            type = request_type::POST;

        /*optional port number given*/
        if (attributes.size() == 4)
            r = new request(type, attributes[1], attributes[2], stoi(attributes[3]));
        else
            r = new request(type, attributes[1], attributes[2], DEFAULT_PORT);
        requests.push(r);
    }
    return requests;
}

// TODO: send data in chunks
int file_reader::read_file(std::string file_path, std::string *buffer) {
    int read_bytes;
    FILE *fp;
    fp = fopen(file_path.c_str(), "r");
    if (fp == nullptr) {
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    read_bytes = ftell(fp);
    rewind(fp);
    char *temp_buffer = new char[read_bytes + 1];
    fread(temp_buffer, sizeof(char), read_bytes, fp);
    *buffer = std::string(temp_buffer);
    delete temp_buffer;
    return read_bytes;
}