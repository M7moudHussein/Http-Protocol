//
// Created by salma on 11/3/18.
//

#include "server_worker.h"

struct thread_arg {
    request *request_to_process;
    response_sender *sender;

    thread_arg(request *request_to_process, response_sender *sender) {
        this->request_to_process = request_to_process;
        this->sender = sender;
    }
};

void *handle_request(void *sender);

response *handle_get_request(request *request_to_process);

server_worker::server_worker(request *req) {
    this->request_to_process = req;
}

void server_worker::process_request(response_sender *res_sender) {
    thread_arg *thread_args = new thread_arg(request_to_process, res_sender);
    int rc = pthread_create(new pthread_t, NULL, handle_request, thread_args);
}

void *handle_request(void *thread_args) {
    thread_arg *args = (thread_arg *) thread_args;
    request *request_to_process = args->request_to_process;
    response_sender *res_sender = args->sender;

    switch (request_to_process->get_type()) {
        case POST:
            res_sender->send_response(&response::RESPONSE_200);
            break;
        case GET:
            res_sender->send_response(handle_get_request(request_to_process));
            break;
        default:
            exit(EXIT_FAILURE);
    }
}

response *handle_get_request(request *request_to_process) {
    //TODO handle different types of files (text, html, images)
}