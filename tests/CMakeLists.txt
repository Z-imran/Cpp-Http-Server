add_executable(run_tests
    RequestsTest.cpp
    ResponseTest.cpp
    ../server/Request.cpp
)

target_link_libraries(run_tests
    gtest
    gtest_main
    pthread
)