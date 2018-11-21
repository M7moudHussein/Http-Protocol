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
                client.process_response(new receiver_args(client.get_socket_fd()));
            } else {
                // TODO HANDLE SENDING ERRORS
            }
            //client.close_connection();
        } else {
            // TODO HANDLE ERRORS
        }
    }
}