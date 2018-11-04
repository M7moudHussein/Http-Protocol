//
// Created by salma on 11/3/18.
//

#include <iostream>
#include <sstream>
#include "file_reader.h"
std::queue<request *> file_reader::parse_requests(std::string request_file) {
    std::queue<request *> requests;
    std::ifstream infile(request_file);
    std::string line;
    while (std::getline(infile, line)) {
        std::vector<std::string> attributes;
        std::stringstream check1(line);
        std::string intermediate;

        // Tokenizing w.r.t. space ' '
        while (getline(check1, intermediate, ' ')) {
            attributes.push_back(intermediate);
        }
        request *r;
        request_type type;
        if (attributes[0] == "GET")
            type = request_type::GET;
        else
            type = request_type::POST;

        /*optional port number given*/
        if (attributes.size() == 4)
            r = new request(type, attributes[1], attributes[2], stoi(attributes[3]));
        else
            r = new request(type, attributes[1], attributes[2]);
        requests.push(r);
    }
    return requests;
}
