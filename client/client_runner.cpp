#include <file_reader.h>
#include "client.h"

/*
 * A driver class to run the client side
 * Use command "./my_client server_ip port_number" to run; where:
 *      server_ip: the IP address of the server
 *      port_number: the port number of the required process on the server
 */
int main(int argc, char const *argv[]) {
    //TODO check on argv
    /* Read requests from input file */
    file_reader reader;
    std::vector<std::string> test_requests = reader.read_requests_file("/input.txt");

    /* Start client, along with its associated threads */
    client client("127.0.0.1");
    client.start();

    /* Connect to the server */
    bool connected = client.establish_connection(8080);
    if (!connected)
        exit(EXIT_FAILURE);

    /* Sequentially process all requests */
    for (const std::string &test_request: test_requests) {
        request *req = new request(test_request);
        client.push_request(req); // add current request to client's queue

        if (req->get_method() == POST)// inform client that a POST request is encountered; so that pipelining will hold
            client.set_post_in_process();

        if (client.send_request(req) < 0) { // check if a request was not sent correctly
            perror("Error while sending new request");
            exit(EXIT_FAILURE);
        }

        while (client.is_post_in_process()); // block sending new requests till post is done
    }

    /* Done */
    client.set_last_request(); // inform client that no more requests are expected
    client.receiver_thread->join(); // wait for background receiver thread to finish its work
}