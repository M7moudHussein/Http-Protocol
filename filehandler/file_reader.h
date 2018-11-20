//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_FILE_READER_H
#define HTTP_PROTOCOL_FILE_READER_H


#include <vector>
#include "string"
#include <fstream>

class file_reader {
public:
    /** parses the requests file for the client */
    std::vector<std::string> read_requests_file(std::string request_file);

    /** Reads the file into the buffer and returns the number of bytes read*/
    int read_file(std::string file_path, std::string *buffer);

    int get_file_size(std::string url);

private:
    std::string get_absolute_url(std::string url);
};


#endif //HTTP_PROTOCOL_FILE_READER_H
