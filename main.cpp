//
// Created by salma on 11/2/18.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include "filehandler/file_reader.h"
#include "client/request.h"

int main(int argc, char const *argv[])
{
    file_reader reader = file_reader();
    std::queue<request*> requests = reader.parse_requests("input.txt");
    std::queue<request*> tmp_q = requests; //copy the original queue to the temporary queue

    while (!tmp_q.empty())
    {
        request *r = tmp_q.front();
        std::cout <<r->get_type()<<" "<<r->get_file_name()<<" "<<r->get_host_name()<<" "<<r->get_port_num()<<"\n";
        tmp_q.pop();
    }

}
