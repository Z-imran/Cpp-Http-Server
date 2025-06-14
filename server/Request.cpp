#include "Request.hpp"
#include "Exceptions/EmptyException.hpp"
#include "Exceptions/MalformedException.hpp"
#include <iostream>


Request  parseRequest(const std::string& raw_request) {
    Request parsed_request = Request();
    if (raw_request.empty()) {
        throw EmptyRequest();
    }

    // First we extract the type of method. We check if the method can be parsed. 
    int pos_method = raw_request.find(" ");
    if (pos_method == std::string::npos) {
        std::cerr << "Unable to parse request method.\n";
        throw MalformedRequest();
    }
    parsed_request.method = raw_request.substr(0, pos_method);

    // Now we parse the path. We check if we can parse the path. 
    int pos_path_start = pos_method + 1; 
    int pos_path_end = raw_request.find(" ", pos_path_start);
    if (pos_path_end == std::string::npos) {
        std::cerr << "Unable to parse request path.\n";
        throw MalformedRequest();
    }
    parsed_request.path = raw_request.substr(pos_path_start, pos_path_end - pos_path_start);

    // Now we parse the version. We check if we can parse the version. 
    int pos_ver_start = pos_path_end + 1; 
    int pos_ver_end = raw_request.find("\r\n");
    if (pos_ver_end == std::string::npos) {
        std::cerr << "Unable to parse request version.\n";
        throw MalformedRequest();
    }
    parsed_request.version = raw_request.substr(pos_ver_start, pos_ver_end - pos_ver_start);

    // Now we parse the headers. For parsing the headers we find th eend of the headers section. 
    // This is marked by "\r\n\r\n" which marks the start of the body. we will use a loop until 
    // the position of the parsed stuff matches the end of the headers. 
    std::unordered_map<std::string, std::string> header_value; 

    int headers_end = raw_request.find("\r\n\r\n");
    if (headers_end == std::string::npos) {
        std::cerr << "Unable to parse request headers.\n";
        throw MalformedRequest();
    }
    int curr_header_start = pos_ver_end + 2;

    // While loop that goes while we are still within the bounds of the header area. 
    while (curr_header_start < headers_end) {
       int curr_header_end = raw_request.find(":", curr_header_start);
       if (curr_header_end ==  std::string::npos) {
        std::cerr << "Unable to parse request headers.\n";
        throw MalformedRequest();
       }
       std::string key = raw_request.substr(curr_header_start, curr_header_end - curr_header_start);

       int curr_value_end = raw_request.find("\r\n", curr_header_start);
       if (curr_value_end ==  std::string::npos) {
        std::cerr << "Unable to parse request headers.\n";
        throw MalformedRequest();
       }
       std::string value = raw_request.substr(curr_header_end + 2, curr_value_end - curr_header_end - 2);
       header_value.insert(std::make_pair(key, value));
       curr_header_start = curr_value_end + 2;
    }

    parsed_request.headers = header_value;


    // Now we parse the body. 
    parsed_request.body = raw_request.substr(headers_end + 4);


    return parsed_request;
    
}