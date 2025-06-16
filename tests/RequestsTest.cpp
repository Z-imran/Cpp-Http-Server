#include <gtest/gtest.h>
#include "../server/Request.hpp"  
#include "../server/Exceptions/EmptyException.hpp"
#include "../server/Exceptions/MalformedException.hpp"


// Tests for the parsing of the incoming request after establishing client-server connection. 



// Tests that we throw an EmptyRequest Exception upon an empty string. 
TEST(RequestTest, EmptyRequest) {
    std::string  empty = "";
    EXPECT_THROW(parseRequest(empty), EmptyRequest);

}


// Tests that we have the req.headers be empty when there arent any headers. 
TEST(RequestTest, NoHeaders) {
    std::string no_headers = "GET / HTTP/1.1\r\n\r\n";
    Request req = parseRequest(no_headers);
    
    EXPECT_EQ(req.method, "GET");
    EXPECT_EQ(req.path, "/");
    EXPECT_EQ(req.version, "HTTP/1.1");
    EXPECT_TRUE(req.headers.empty());
    EXPECT_EQ(req.body, "");
}


// Tests that upon malformed header(s) we throw a MalformedRequest Exception.
TEST(RequestTest, MalformedHeader) {

    // Check for one. 
    std::string malformed = "GET /hello HTTP/1.1\r\n"
                            "MALFORMEDHEADERNOCOLON\r\n\r\n";

    EXPECT_THROW(parseRequest(malformed), MalformedRequest);

    // Check to make sure nothing out of order on two. 
    std::string malformed_two = "GET /hello HTTP/1.1\r\n"
                            "MALFORMEDHEADERNOCOLON\r\n"
                            "MALFORMEDHEADERNOCOLON2\r\n\r\n";

    EXPECT_THROW(parseRequest(malformed_two), MalformedRequest);

    // Check to make sure that nothing happens on second header being valid. 
    std::string malformed_three = "GET /hello HTTP/1.1\r\n"
                            "MALFORMEDHEADERNOCOLON\r\n"
                            "Host: STUFF\r\n\r\n";

    EXPECT_THROW(parseRequest(malformed_three), MalformedRequest);

}

// Check if the request correctly produces a MalformedRequest if missing whitespaces.
TEST(RequestTest, NoWhitespace) {
    
    // No whitespace after GET
    std::string no_whitespace_get = "GET/ HTTP/1.1\r\n\r\n"; 
    EXPECT_THROW(parseRequest(no_whitespace_get), MalformedRequest);

    // No whitespace after path
    std::string no_whitespace_path = "GET /HTTP/1.1\r\n\r\n"; 
    EXPECT_THROW(parseRequest(no_whitespace_path), MalformedRequest);

}

// Test that lines end with \r\n.
TEST(RequestTest, NoLineEnding) {
    std::string missing_ending = "GET / HTTP/1.1\nHost: localhost\r\n\r\n";
    EXPECT_THROW(parseRequest(missing_ending), MalformedRequest);
}


// Test that valid requests are correctly handled. 
TEST(RequestTest, Valid) {
    std::string valid =  "GET /hello HTTP/1.1\r\n"
                         "Host: localhost:8080\r\n"
                         "User-Agent: curl/8.7.1\r\n"
                         "Accept: */*\r\n"
                         "\r\n";
    Request req = parseRequest(valid);


    EXPECT_EQ(req.method, "GET");
    EXPECT_EQ(req.path, "/hello");
    EXPECT_EQ(req.version, "HTTP/1.1");
    EXPECT_EQ(req.headers["Host"], " localhost:8080");
    EXPECT_EQ(req.headers["User-Agent"], " curl/8.7.1");
    EXPECT_EQ(req.headers["Accept"], " */*");
    EXPECT_EQ(req.body, "");
}