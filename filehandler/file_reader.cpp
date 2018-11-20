#include <sstream>
#include <zconf.h>
#include <iostream>
#include "file_reader.h"

std::vector<std::string> file_reader::read_requests_file(std::string request_file) {
    std::vector<std::string> client_requests;
    std::ifstream input_file_stream(request_file);
    std::string line;
    while (std::getline(input_file_stream, line)) {
        client_requests.push_back(line);

    }
    return client_requests;
}

// TODO: send data in chunks
int file_reader::read_file(std::string url, std::string *buffer) {
    std::string absolute_path = get_absolute_url(url);
    int read_bytes = get_file_size(url);
    FILE *fp;
    fp = fopen(absolute_path.c_str(), "r");
    if (fp == nullptr) {
        return -1;
    }
    char *temp_buffer = new char[read_bytes + 1];
    fread(temp_buffer, sizeof(char), read_bytes, fp);
    *buffer = std::string(temp_buffer);
    delete[] temp_buffer;
    return read_bytes;
}

int file_reader::get_file_size(std::string url) {
    std::string absolute_path = get_absolute_url(url);
    FILE *fp;
    fp = fopen(absolute_path.c_str(), "r");
    if (fp == nullptr) {
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

std::string file_reader::get_absolute_url(std::string url) {
    int const max_path_length = 200;
    char cwd[max_path_length];
    getcwd(cwd, sizeof(cwd));
    return std::string(cwd) + url;
}