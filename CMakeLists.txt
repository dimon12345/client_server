cmake_minimum_required(VERSION 3.22.0)
project(tcp)

add_executable(client client_main.cpp Client.cpp ClientSocket.cpp)
add_executable(server server_main.cpp Server.cpp ServerSocket.cpp InputHandlerThread.cpp LineLogger.cpp)
