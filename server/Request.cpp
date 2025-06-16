#include "Request.hpp"
#include "Exceptions/EmptyException.hpp"
#include "Exceptions/MalformedException.hpp"
#include <iostream>


// Request  parseRequest(const std::string& raw_request) {
//     Request parsed_request = Request();
//     if (raw_request.empty()) {
//         throw EmptyRequest();
//     }

//     // First we extract the type of method. We check if the method can be parsed. 
//     int pos_method = raw_request.find(" ");
//     if (pos_method == std::string::npos) {
//         std::cerr << "Unable to parse request method.\n";
//         throw MalformedRequest();
//     }
//     parsed_request.method = raw_request.substr(0, pos_method);

//     // Now we parse the path. We check if we can parse the path. 
//     int pos_path_start = pos_method + 1; 
//     int pos_path_end = raw_request.find(" ", pos_path_start);
//     if (pos_path_end == std::string::npos) {
//         std::cerr << "Unable to parse request path.\n";
//         throw MalformedRequest();
//     }
//     parsed_request.path = raw_request.substr(pos_path_start, pos_path_end - pos_path_start);

//     // Now we parse the version. We check if we can parse the version. 
//     int pos_ver_start = pos_path_end + 1; 
//     int pos_ver_end = raw_request.find("\r\n");
//     if (pos_ver_end == std::string::npos) {
//         std::cerr << "Unable to parse request version.\n";
//         throw MalformedRequest();
//     }
//     parsed_request.version = raw_request.substr(pos_ver_start, pos_ver_end - pos_ver_start);

//     // Now we parse the headers. For parsing the headers we find th eend of the headers section. 
//     // This is marked by "\r\n\r\n" which marks the start of the body. we will use a loop until 
//     // the position of the parsed stuff matches the end of the headers. 
//     std::unordered_map<std::string, std::string> header_value; 

//     int headers_end = raw_request.find("\r\n\r\n");
//     if (headers_end == std::string::npos) {
//         std::cerr << "Unable to parse request headers.\n";
//         throw MalformedRequest();
//     }
//     int curr_header_start = pos_ver_end + 2;

//     // While loop that goes while we are still within the bounds of the header area. 
//     while (curr_header_start < headers_end) {
//        int curr_header_end = raw_request.find(":", curr_header_start);
//        if (curr_header_end ==  std::string::npos) {
//         std::cerr << "Unable to parse request headers.\n";
//         throw MalformedRequest();
//        }
//        std::string key = raw_request.substr(curr_header_start, curr_header_end - curr_header_start);

//        int curr_value_end = raw_request.find("\r\n", curr_header_start);
//        if (curr_value_end ==  std::string::npos) {
//         std::cerr << "Unable to parse request headers.\n";
//         throw MalformedRequest();
//        }
//        std::string value = raw_request.substr(curr_header_end + 2, curr_value_end - curr_header_end - 2);
//        header_value.insert(std::make_pair(key, value));
//        curr_header_start = curr_value_end + 2;
//     }

//     parsed_request.headers = header_value;


//     // Now we parse the body. 
//     parsed_request.body = raw_request.substr(headers_end + 4);


//     return parsed_request;
    
// }

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