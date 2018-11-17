#ifndef HTTP_PROTOCOL_FILE_WRITER_H
#define HTTP_PROTOCOL_FILE_WRITER_H
#include <string>
class file_writer {
public:
    void write(const char *file_name, std::string buffer, int buffer_size);
};

#endif

