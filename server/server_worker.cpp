//
// Created by salma on 11/3/18.
//

#include <iostream>
#include <file_reader.h>
#include "server_worker.h"

struct thread_args {
    int socket_no;
    request *request_to_process;

    thread_args(int socket_no, request *request_to_process) {
        this->socket_no = socket_no;
        this->request_to_process = request_to_process;
    }
};

void *handle_request(void *sender);

response *handle_get_request(request *request_to_process);

server_worker::server_worker(request *request_to_process, int socket_no) {
    this->request_to_process = request_to_process;
    this->socket_no = socket_no;
}

void server_worker::process_request() {
    thread_args *args = new thread_args(socket_no, request_to_process);
    int rc = pthread_create(new pthread_t, NULL, handle_request, args);
}

void *handle_request(void *arguments) {
    thread_args *args = (thread_args *) arguments;
    request *request_to_process = args->request_to_process;
    int socket_no = args->socket_no;
    response *res;
    switch (request_to_process->get_type()) {
        case POST:
            //TODO set res to 200 OK or whatever
            break;
        case GET:
            res = handle_get_request(request_to_process);
            break;
        default:
            exit(EXIT_FAILURE);
    }
    int test = send(socket_no, res->to_string(), res->get_length(), 0);
    std::cout << test << std::endl;
}

response *handle_get_request(request *request_to_process) {
    char *file_data;
    int data_length;
    file_reader reader;
    data_length = reader.read_file(request_to_process->get_path(), &file_data);
    if (data_length == -1) {
        //TODO send 404
    } else {
        //TODO set request body
    }
}