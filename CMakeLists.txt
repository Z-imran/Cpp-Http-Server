cmake_minimum_required(VERSION 3.10) 

project(HTTPServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(httpserver 
    main.cpp
    server/Server.cpp
    )

include_directories(
    server

)