#include "Response.hpp"

// Class implementation of the Response.hpp file.

Response::Response() {
    this->status_code = 0;
    this->status_message = "";
    this->headers = std::unordered_map<std::string, std::string>();
    this->body = "";
}


Response::~Response() {
    return;
}

Response Response::buildResponse(int status_code,const std::string& msg,  const std::string& body, const std::string type) {
    // Sets the objects status code to be the same. 

    this->status_code = status_code;
    this->status_message = msg;
    this->body = body;
    this->headers["Content-Type"] = type;
    this->headers["Content-Length"] = std::to_string(body.size());
    return *this;
}


std::string Response::toHTTP() {
    if (status_code == 0 || status_message == "" || headers.empty() || body == "") {
        std::string body = "Unable to build a response";
        std::ostringstream basic; 
        basic <<  "HTTP/1.1 500 Internal Server Error\r\n";
        basic << "Content-Type: text/html\r\n";
        basic << "Content-Length: " << body.length() << "\r\n\r\n" << body; 
        return basic.str();
    }
    std::ostringstream http;
    http << "HTTP/1.1 " << status_code << " " << status_message <<  "\r\n";
    for (const std::pair<const std::string, std::string>& header : headers) {
        http << header.first << ": " << header.second << "\r\n";
    }
    http << "\r\n" << body;

    return http.str();
}

Response Response::addHeader(const std::string& key, const std::string& value) {
    this->headers[key] = value;
    return *this;
}
