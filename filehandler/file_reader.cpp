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
    int file_size = get_file_size(url);
    FILE *fp = fopen(absolute_path.c_str(), "r");
    if (fp == NULL) {
        return -1;
    }
    char temp_buffer[file_size];
    int read_bytes = fread(temp_buffer, sizeof(char), read_bytes, fp);
    fclose(fp);
    if (read_bytes != file_size) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }
    *buffer = std::string(temp_buffer, file_size);
    return file_size;
}

int file_reader::get_file_size(std::string url) {
    std::string absolute_path = get_absolute_url(url);
    FILE *fp = fopen(absolute_path.c_str(), "r");
    if (fp == nullptr) {
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    int file_size = ftell(fp);
    fclose(fp);
    return file_size;
}

std::string file_reader::get_absolute_url(std::string url) {
    int const max_path_length = 200;
    char cwd[max_path_length];
    getcwd(cwd, sizeof(cwd));
    return std::string(cwd) + url;
}