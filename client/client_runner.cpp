//TODO in properties url. define HTTP_VERSION 1.0
#include <file_reader.h>
#include <iostream>
#include "client.h"

#define MAX_BUFFER_SIZE 1452 //TODO properties

int main(int argc, char const *argv[]) {
    //TODO check on argv
    file_reader reader;
    std::vector<std::string> test_requests = reader.read_requests_file("/input.txt");
    client client("127.0.0.1");
    client.start();
    bool connected = client.establish_connection(8080);
    if (!connected)
        exit(EXIT_FAILURE);
    for (std::string test_request: test_requests) {
        request *req = new request(test_request);
        client.set_current_request(req);
        if (client.send_request(req) < 0) {
            // TODO HANDLE SENDING ERRORS
        }
        //client.close_connection();
    }
    int x = 0;
    while (true) {
        x++;
        if (x == 1000000000) {
            x = x / 2;
        }
        if (x == -1) {
            break;
        }
    }
    std::cout << x << std::endl;
}