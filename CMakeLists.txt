cmake_minimum_required(VERSION 3.12)
project(Http_Protocol)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_STANDARD 14)

include_directories(client)
include_directories(filehandler)
include_directories(models)
include_directories(server)

add_executable(Client_side
        client/client.cpp
        client/client.h
        client/client_runner.cpp
        filehandler/file_reader.cpp
        filehandler/file_reader.h
        filehandler/file_writer.cpp
        filehandler/file_writer.h
        models/request.cpp
        models/request.h
        models/response.cpp
        models/response.h
        )
add_executable(Server_side
        server/server_dispatcher.cpp
        server/server_dispatcher.h
        server/server_runner.cpp
        server/server_worker.cpp
        server/server_worker.h
        filehandler/file_reader.cpp
        filehandler/file_reader.h
        filehandler/file_writer.cpp
        filehandler/file_writer.h
        models/request.cpp
        models/request.h
        models/response.cpp
        models/response.h)
