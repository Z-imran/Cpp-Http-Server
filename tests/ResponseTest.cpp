#include <gtest/gtest.h>
#include "../server/Response.hpp"   
#include "../server/Exceptions/EmptyException.hpp"
#include "../server/Exceptions/MalformedException.hpp"


// Tests for the Response class and its Response method.


// Tests that we correctly build a response using the constructor. 
TEST(ResponseTest, ConstructorTest) {
    Response response = Response(); 
    EXPECT_EQ(response.status_code, 0);
    EXPECT_EQ(response.status_message, "");
    EXPECT_TRUE(response.headers.empty());
    EXPECT_EQ(response.body, "");
}

// Tests that an ok response is correctly built. 
TEST(ResponseTest, buildResponseOK) {
    Response res = Response(); 
    res.buildResponse(200, "OK", "TEST", "text/html");
    EXPECT_EQ(res.status_code, 200);
    EXPECT_EQ(res.status_message, "OK");
    EXPECT_EQ(res.headers["Content-Type"], "text/html");
    EXPECT_EQ(res.headers["Content-Length"], "4");
    EXPECT_EQ(res.body, "TEST");
}

// Tests that an ok response is correctly built. 
TEST(ResponseTest, BuildResponseNotFound) {
    Response res = Response(); 
    res.buildResponse(404, "Not Found", "Not Found", "application/json");
    EXPECT_EQ(res.status_code, 404);
    EXPECT_EQ(res.status_message, "Not Found");
    EXPECT_EQ(res.headers["Content-Type"], "application/json");
    EXPECT_EQ(res.headers["Content-Length"], "9");
    EXPECT_EQ(res.body, "Not Found");
}

// Test that we properly create a valid HTTP response. 
TEST(ResponseTest, responseToHTTP) {
    Response res = Response(); 
    res.buildResponse(200, "OK", "TEST", "text/html");
    EXPECT_EQ(res.status_code, 200);
    EXPECT_EQ(res.status_message, "OK");
    EXPECT_EQ(res.headers["Content-Type"], "text/html");
    EXPECT_EQ(res.headers["Content-Length"], "4");
    EXPECT_EQ(res.body, "TEST");

    std::string expected = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html\r\n"
                           "Content-Length: 4\r\n"
                           "\r\n"
                           "TEST";
    std::string test = res.toHTTP();
    EXPECT_TRUE(test.find("Content-Type: text/html\r\n") != std::string::npos);
    EXPECT_TRUE(test.find("Content-Length: 4\r\n") != std::string::npos);
    EXPECT_TRUE(test.find("\r\nTEST") != std::string::npos);
    EXPECT_TRUE(test.find("HTTP/1.1 200 OK\r\n") != std::string::npos);

}


TEST(ResponseTest, addHeader) {
    Response res = Response(); 
    res.buildResponse(200, "OK", "TEST", "text/html");
    res.addHeader("test", "testval");
    EXPECT_EQ(res.status_code, 200);
    EXPECT_EQ(res.status_message, "OK");
    EXPECT_EQ(res.headers["Content-Type"], "text/html");
    EXPECT_EQ(res.headers["Content-Length"], "4");
    EXPECT_EQ(res.headers["test"], "testval");
    EXPECT_EQ(res.body, "TEST");
}