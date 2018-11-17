#include <stdio.h>
#include <iostream>
#include "file_writer.h"

void file_writer::write(const char *file_name, std::string buffer, int buffer_size) {
    FILE *file = fopen(file_name, "w");
    std::cout<<buffer<<"\n";
    fwrite(buffer.c_str(), sizeof(char), buffer_size, file);
    fclose(file);
}
