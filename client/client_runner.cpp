//TODO in properties file. define HTTP_VERSION 1.0
#include <request.h>
#include <file_reader.h>
#include "queue"
#include "client.h"

#define MAX_BUFFER_SIZE 1452 //TODO properties

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
                char *res_msg;
                if (recv(client.get_socket_fd(), res_msg, MAX_BUFFER_SIZE, 0) >= 0) {
                    response *res = new response();
                    res->build(res_msg);
                    if (res->get_status() == Status_code::CODE_200) {
                        if (req->get_type() == GET)
                            client.handle_get_response(req, res);
                        else
                            client.handle_post_request();
                    } else {
                        // TODO HANDLE 'NOT FOUND' ERROR
                    }
                } else {
                    // TODO HANDLE RECEIVING ERRORS
                }
            } else {
                // TODO HANDLE SENDING ERRORS
            }
            client.close_connection();
        } else {
            // TODO HANDLE ERRORS
        }
    }
}
