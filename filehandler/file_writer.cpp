#include <stdio.h>
#include "file_writer.h"

void file_writer::write(const char *file_name, char *buffer, int buffer_size) {
    FILE *file = fopen(file_name, "w");
    fwrite(buffer, sizeof(char), buffer_size, file);
    fclose(file);
}
