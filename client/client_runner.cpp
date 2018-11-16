//
// Created by salma on 11/8/18.
//
//TODO in properties file. define HTTP_VERSION 1.0
#include <request.h>
#include <file_reader.h>
#include "queue"
#include "client.h"

int main(int argc, char const *argv[]) {
    //TODO check on argv
    file_reader reader;
    std::queue<request *> requests = reader.parse_requests("input.txt");
    client client(argv[1]);
    while (!requests.empty()) {
        request *req = requests.front();
        requests.pop();
        bool connected = client.establish_connection(req->get_port_num());
        if (connected) {
            if (client.send_request(req) >= 0) {
                //handle post and get requests;
            } else {
                //TODO HANDLE SENDING ERRORS
            }
        } else {
            //TODO HANDLE ERRORS
        }
    }
}
