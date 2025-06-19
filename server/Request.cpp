#include "Request.hpp"
#include "Exceptions/EmptyException.hpp"
#include "Exceptions/MalformedException.hpp"
#include <iostream>

// We parse line by line. The first line should have three components seperated by " " and if it doesnt then we 
// know we have an error (MalformedRequest). Then we should check for headers and parse each header line by line. 
// We then throw wahtever remains into the body. 
Request parseRequest(const std::string& raw_request) {
    // If string is empty throw an EmptyRequest exception.
    if (raw_request.empty()) {
        throw EmptyRequest();
    }

    Request parsed; 

    // find the end of the first line denoted by "\r\n". If the not found throw a MalformedRequest Exception.
    size_t first_line_end = raw_request.find("\r\n");
    if (first_line_end == std::string::npos) {
        throw MalformedRequest();
    }

    // Now check for three seperate components and then assign the respective components.
    std::string request_line = raw_request.substr(0, first_line_end);
    size_t method_pos = request_line.find(" ");
    if (method_pos == std::string::npos) {
        throw MalformedRequest();
    }
    size_t path_pos = request_line.find(" ", method_pos + 1);
    if (path_pos == std::string::npos) {
        throw MalformedRequest();
    }

    parsed.method = request_line.substr(0, method_pos);
    parsed.path = request_line.substr(method_pos + 1, path_pos - method_pos - 1);
    parsed.version = request_line.substr(path_pos + 1);

    if (parsed.method.empty() || parsed.path.empty() || parsed.version.empty()
        || parsed.version.find(" ") != std::string::npos) {
        throw MalformedRequest();
    }

    // We now build the header parsing part. 
    std::unordered_map<std::string, std::string> header_value;
    int headers_end = raw_request.find("\r\n\r\n");
    if (headers_end == std::string::npos) {
        throw MalformedRequest();
    }


    size_t header_start = first_line_end + 2;
    while (header_start < headers_end) {

        // If the next line is non existent or past the headers end then throw MalformedRequest exception. 
        size_t line_end = raw_request.find("\r\n", header_start);
        if (line_end == std::string::npos || line_end > headers_end) {
            throw MalformedRequest();
        }

        // If the colon seperator is not there then throw MalformedRequest exception. 
        std::string header_line = raw_request.substr(header_start, line_end - header_start);
        size_t colon_pos = header_line.find(":");
        if (colon_pos == std::string::npos) {
            throw MalformedRequest();
        }

        std::string key = header_line.substr(0, colon_pos);
        std::string value = header_line.substr(colon_pos + 1);

        header_value.insert(std::make_pair(key, value));
        header_start = line_end + 2;
    }

    parsed.headers = header_value;


    parsed.body = raw_request.substr(headers_end + 4);

    return parsed;
        
}


std::string getMimeType(const std::string& path) {
    return "";
}