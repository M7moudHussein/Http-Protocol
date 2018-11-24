#include <file_reader.h>
#include "client.h"

int main(int argc, char const *argv[]) {
    //TODO check on argv
    file_reader reader;
    std::vector<std::string> test_requests = reader.read_requests_file("/input.txt");
    client client("127.0.0.1");
    client.start();
    bool connected = client.establish_connection(8080);
    if (!connected)
        exit(EXIT_FAILURE);

    for (const std::string &test_request: test_requests) {
        request *req = new request(test_request);

        if (req->get_method() == POST)
            client.set_post_in_process();

        if (client.send_request(req) < 0) {
            perror("Error while sending new request");
            exit(EXIT_FAILURE);
        }

        client.set_current_request(req);

        while (client.is_post_in_process()); // block sending new requests till post is done
    }
    client.receiver_thread->join();
    client.close_connection();
}