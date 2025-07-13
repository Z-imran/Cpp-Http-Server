#include <string>
#include <unordered_map>
#include <sstream>
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
     * If the status code is not common defaults to generic message. <<CONSIDER ADDING HEADERS>>
     * 
     * @param status_code sets the status code of the Response to be the same. 
     * @param msg is the corresponsfing status message. 
     * @param body sets the body of the response to contain the resulting message. 
     * @param type contains the MIME type of the response. 
     * 
     */
    Response buildResponse(int status_code,const std::string& msg,  const std::string& body, const std::string type);


    /**
     * @brief Converts the Response into a valid string for HTTP repsonse. 
     * 
     * Formats a string to be a valid HTTP response. Will always format based on the response struct so on a non built response
     * this will make an empty string
     */
    std::string toHTTP();

    /**
     * @brief Adds a Key/Value pair into the headers.
     * 
     * Sets the key of the new pair to be the specified key value and the value as provided.
     *  
     * @param key The key of the header map pair.
     * @param value the value of the header map pair.
     * @return The response object. 
     */
    Response addHeader(const std::string& key, const std::string& value);
};








#endif