#include <string>
#include <unordered_map>

#ifndef REQUEST_UNIQUE
#define REQUEST_UNIQUE


/**   Struct for the Requests that are parsed from the parseRequest(String& raw_request) function. 
 *    Struct represents the oarsed contents of the raw_request that is recieved from the client. 
 */ 

struct Request {
    std::string method;                                      // The "function" that we are doing to the server.
    std::string path;                                        // The "target path" or location being requested. 
    std::string version;                                     // The HTTP version of the request.
    std::unordered_map<std::string, std::string> headers;    // The Key-value of header fields.
    std::string body;                                        // The extra information (Typically empty in GET).
};


/**
 * @brief Parses raw Request. 
 * 
 * Recieves a string that is the raw request of the client. The parses the string into a Request struct. 
 * 
 * @param raw_request the raw unparse request recieved form the client. 
 * 
 * @return Returns a complete Request Struct that contains all necessary information. (body May be Empty in GET). 
 */
Request parseRequest(const std::string& raw_request); 


/**
 * @brief Gets MIME type.
 * 
 * Parses the Requests path to get the MIME type. Should the MIME type not be a valid type it defaults to text. 
 * 
 * @param path the Requests path variable containing the MIME type extension if a valid request. 
 * 
 * @return Returns a string that contains the correct MIME type. 
 */

std::string getMimeType(const std::string& path);


#endif 