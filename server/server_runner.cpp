#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "server_dispatcher.h"

/*server runner initiates the server to run on a certain port*/
int main(int argc, char const *argv[]) {
    if (argc == 2) {
        int portNo = atoi(argv[1]);
        server_dispatcher::run_server(portNo);
    } else {
        perror("Invalid port number");
        exit(EXIT_FAILURE);
    }
}
