add_executable(run_tests
    RequestsTest.cpp
    ResponseTest.cpp
    ../server/Request.cpp
    ../server/Response.cpp
    ../server/ThreadPool.cpp
)

target_link_libraries(run_tests
    gtest
    gtest_main
    pthread
)