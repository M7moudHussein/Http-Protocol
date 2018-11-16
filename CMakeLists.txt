cmake_minimum_required(VERSION 3.12)
project(Http_Protocol)

set(CMAKE_CXX_STANDARD 14)

include_directories(client)
include_directories(filehandler)
include_directories(models)
include_directories(server)

add_executable(Http_Protocol
        client/client.cpp
        client/client.h
        filehandler/file_reader.cpp
        filehandler/file_reader.h
        models/request.cpp
        models/request.h
        models/response.cpp
        models/response.h
        server/server_dispatcher.cpp
        server/server_dispatcher.h
        server/server_runner.cpp
        server/server_worker.cpp
        server/server_worker.h client/client_runner.cpp)
