#include <stdio.h>
#include <iostream>
#include <zconf.h>
#include "file_writer.h"

void file_writer::write(std::string url, std::string buffer) {
    std::string absolute_url = get_absolute_url(url);
    FILE *file = fopen(absolute_url.c_str(), "a");
    fwrite(buffer.c_str(), sizeof(char), buffer.length(), file);
    fclose(file);
}

std::string file_writer::get_absolute_url(std::string url) {
    int const max_path_length = 200;
    char cwd[max_path_length];
    getcwd(cwd, sizeof(cwd));
    return std::string(cwd) + url;
}