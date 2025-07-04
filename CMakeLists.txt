cmake_minimum_required(VERSION 3.10) 

project(HTTPServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(httpserver 
    main.cpp
    server/Server.cpp
    server/Request.cpp
    server/Response.cpp
    )

include_directories(
    server

)

enable_testing()
add_subdirectory(tests)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)