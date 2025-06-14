#include <gtest/gtest.h>
#include "../server/Request.hpp"  
#include "../server/Exceptions/EmptyException.hpp"


// Tests for the parsing of the incoming request after establishing client-server connection. 

TEST(RequestTest, EmptyRequest) {
    std::string  empty = "";
    EXPECT_THROW(parseRequest(empty), EmptyRequest);

}