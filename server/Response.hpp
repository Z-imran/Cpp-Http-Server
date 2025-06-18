#include <string>
#include <unordered_map>
#include "Request.hpp"
#ifndef RESPONSE_UNIQUE
#define RESPONSE_UNIQUE

// Class template for the HTTP response. Contains the variables required for the http response and
// a handleResponse function and a toHTTP function that handles the incoming request to convert it 
// into a valid HTTP response. 

class Response {
    public: 
        
    int status_code;                                        // The code corrresponding to the status of the response.
    std::string status_message;                             // The correspinsding status meesage.
    std::unordered_map<std::string, std::string> headers;   // The Key-value of header fields.
    std::string body;                                       // The extra information.


    /**
     * @brief constructor/deconstructor for a Response. 
     * 
     * Creates/Destroys the resposne object.
     * 
     */
    Response();
    ~Response();


    /**
     * @brief Builds the response object based on the input request. 
     * 
     * Makes the response object contain the correct values for the corresponding variables. Uses a map for common status codes. 
     * If the status code is not common defaults to generic message. 
     * 
     */
    Response buildResponse();


    /**
     * @brief Converts the Response into a valid string for HTTP repsonse. 
     * 
     * Formats a string to be a valid HTTP response. 
     */
    std::string toHTTP();
};








#endif