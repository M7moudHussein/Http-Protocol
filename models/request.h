//
// Created by salma on 11/3/18.
//

#ifndef HTTP_PROTOCOL_REQUEST_H
#define HTTP_PROTOCOL_REQUEST_H

#include <string>

enum request_type {
    GET,
    POST
};

class request {
public:
    request() {};

    request(request_type type, std::string file_name, std::string host_name, int port_num);

    void set_type(request_type r_type);

    request_type get_type();

    void set_path(std::string path);

    std::string get_path();

    void set_file_name(std::string file_name);

    std::string get_file_name();

    void set_host_name(std::string host_name);

    std::string get_host_name();

    void set_port_num(int port_num);

    int get_port_num();


private:
    request_type type;
    std::string path;
    std::string file;
    std::string host;
    int port_number;
};


#endif //HTTP_PROTOCOL_REQUEST_H
