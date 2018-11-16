#ifndef HTTP_PROTOCOL_FILE_WRITER_H
#define HTTP_PROTOCOL_FILE_WRITER_H

class file_writer {
public:
    void write(const char *file_name, char *buffer, int buffer_size);
};

#endif

