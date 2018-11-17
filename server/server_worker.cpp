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

response *handle_post_request(request *request_to_process);

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
            res = handle_post_request(request_to_process);
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
        response *res = new response();
        res->set_http_version(request_to_process->get_http_version());
        res->set_status(CODE_200);
        res->set_body(file_data, data_length);
//        const char *mime;
//        magic_t magic = magic_open(MAGIC_MIME_TYPE);
//        magic_load(magic, NULL);
//        magic_compile(magic, NULL);
//        mime = magic_file(magic, request_to_process->get_path().c_str());
//        magic_close(magic);

        std::string extension;
        for (int i = request_to_process->get_path().length() - 1; i >= 0; i--) {
            if (request_to_process->get_path()[i] == '.') {
                extension = request_to_process->get_path().substr(i + 1);
            }
        }

        std::string content_type;
        if (extension == "txt") {
            content_type = "text/plain";
        } else if (extension == "html") {
            content_type = "text/html";
        } else {
            content_type = "image" + std::string("/") + extension;
        }

        res->set_content_type(content_type.c_str());
        return res;
    }
}

response *handle_post_request(request *request_to_process){
    /*1. send OK response before client can upload file to server*/
    response *res = new response();
    res->set_http_version(request_to_process->get_http_version());
    res->set_status(CODE_200);
    /*2. save the uploaded file by the client to the server directory*/
    //writer.write(request_to_process->get_path().c_str(), req->get_body(), req->get_body_length());
    return res;
}