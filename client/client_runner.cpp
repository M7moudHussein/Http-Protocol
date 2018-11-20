//TODO in properties url. define HTTP_VERSION 1.0
#include <file_reader.h>
#include <iostream>
#include "client.h"

#define MAX_BUFFER_SIZE 1452 //TODO properties

int main(int argc, char const *argv[]) {
    //TODO check on argv
    file_reader reader;
    std::vector<std::string> test_requests = reader.read_requests_file("input.txt");
    client client(argv[1]);
    for (std::string test_request: test_requests) {
        request *req = new request(test_request);
        bool connected = client.establish_connection(req->get_port_num());
        if (connected) {
            if (client.send_request(req) >= 0) {
                char *response_buffer = new char[MAX_BUFFER_SIZE];
                ssize_t read_data_length = recv(client.get_socket_fd(), response_buffer, MAX_BUFFER_SIZE, 0);
                if (read_data_length >= 0) {
                    response *res = new response();
                    res->build(std::string(response_buffer, read_data_length));
                    if (res->get_status() == response_status_code::CODE_200) {
                        if (req->get_method() == GET) {
                            client.handle_get_response(req, res);
                        } else {
                            client.handle_post_request(req);
                        }
                    } else {
                        // TODO HANDLE 'NOT FOUND' ERROR
                    }

                    delete res;
                } else {
                    // TODO HANDLE RECEIVING ERRORS
                }

                delete[] response_buffer;
            } else {
                // TODO HANDLE SENDING ERRORS
            }
            //client.close_connection();
        } else {
            // TODO HANDLE ERRORS
        }
    }
}