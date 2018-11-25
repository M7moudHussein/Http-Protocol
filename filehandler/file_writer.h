#ifndef HTTP_PROTOCOL_FILE_WRITER_H
#define HTTP_PROTOCOL_FILE_WRITER_H

#include <string>

class file_writer {
public:
    /* Writes data identified by 'buffer' in the file identified by 'url' */
    void write(std::string url, std::string buffer);

private:
    std::string get_absolute_url(std::string url);
};

#endif

