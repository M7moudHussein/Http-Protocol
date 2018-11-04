//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_FILE_READER_H
#define HTTP_PROTOCOL_FILE_READER_H


#include <queue>
#include "string"
#include <fstream>
#include "../client/request.h"

class file_reader {
public:
/*parses the requests file for the client */
    std::queue<request *> parse_requests(std::string request_file);
};


#endif //HTTP_PROTOCOL_FILE_READER_H
