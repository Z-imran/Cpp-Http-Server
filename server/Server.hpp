#include "Response.hpp"
#ifndef SERVER_UNIQUE
#define SERVER_UNIQUE

/**   Class template for the server. Contains two int variables (port, server_fd) and 
 *  functions for start, run, acceptClient, and setupSocket. The Server wil be created 
 *  in main and will be able to listen for multiple clinet requests and will eventually 
 *  be able to handle them asynchronously. 
 */ 
class Server {
    public: 
    /** 
     * @brief Constrcutor for the server. 
     *  
     * Creates/Destroys the server object and assigns the port number provided to the variable.
     * 
     * @param port port number that the server is socket is binded to. 
     */
    explicit Server(int port); 
    ~Server();

    /**
     * @brief Starts the server. 
     * 
     * Startup function which creates a socket and binds it to a port ready for listening.
     * 
     * @return true if server was sucessfully started, false if otherwise. 
     */
    bool start();


    /** 
     * @brief  Runs the Server. 
     * 
     * Main runing loop that accepts clients and handles all the logic for queuing into a threadpool
     * For now this is simply one client.
     * 
     */
    void run();

    /** 
     * @brief Accepts incoming client. 
     * 
     * Accepts the incoming client which then returns the socket id. 
     * 
     * @return returns the client socket id. 
     */
    int acceptClient();


    /**
     * @brief handles the request and does the action based on the method. 
     * 
     * Based of the corresponding method produced from parseRequest this function does the action. 
     * Should the request be malformed the response should be error code 400 (BAD_REQUEST).
     * 
     * @param req is the intake request parsed from the clients request string. 
     * @return returns a response object that containing the corresponding response information. 
     */
    Response handleRequest(const Request& req);

    /**
     * @brief Reads the file based of provided path. 
     * 
     * Reads the file based of the provided path. if the path is empty or invalid then we create an
     * invalid response 404 stating "File Not Found". 
     * 
     * @param path is the intake path provided by req.path. 
     * @return returns a response object. 
     */
    Response readFile(const std::string& path);

    /**
     * @brief places the file into the public directory. 
     * 
     * Places the file into public folder and currently replaces the file if it already exists. 
     * produces response with error 500, "Internal Server Error" on failure of the PUT. 
     * 
     * @param path is the intake path provided by req.path. 
     * @param body is the intake file provided by req.body. 
     * @return returns a response object. 
     */
    Response putFile(const std::string& path, const std::string& body);

    /** 
     * @brief shows the options available for requests to the server. 
     * 
     * Creates a response object that contains an additional header with the available options based
     * off the OPTIONS method. 
     * 
     * @return returns a resposne object. 
     */
    Response showOptions();

        /**
     * @brief Sends the headers of the File. 
     * 
     * shows the headers of the file based of the provided path. if the path is empty or invalid then we create an
     * invalid response 404 stating "File Not Found". 
     * 
     * @param path is the intake path provided by req.path. 
     * @return returns a response object. 
     */
    Response headersOfFile(const std::string& path);

    /**
     * @brief Deletes the File based on path. 
     * 
     * Deletes the file based of the provided path. if the path is empty or invalid then we create an
     * invalid response 404 stating "File Not Found". 
     * 
     * @param path is the intake path provided by req.path. 
     * @return returns a response object. 
     */
    Response deleteFile(const std::string& path);

    // deletes any copies and assignments to make sure that the server has only one point of entry. 
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    private: 

    int port; 
    int server_fd; 
    bool running; 
    
    /**
     * @brief Sets up the socket. 
     * 
     * Creates the socket for this server. 
     * 
     * @return true if socket was created properly, false if otherwise. 
     */
    bool setUpSocket(); 

};


#endif
