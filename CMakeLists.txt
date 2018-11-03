cmake_minimum_required(VERSION 3.12)
project(Http_Protocol)

set(CMAKE_CXX_STANDARD 14)

add_executable(Http_Protocol
        main.cpp server/server_dispatcher.cpp server/server_dispatcher.h server/server_worker.cpp server/server_worker.h server/response.cpp server/response.h client/request.cpp client/request.h client/client.cpp client/client.h filehandler/file_reader.cpp filehandler/file_reader.h)
