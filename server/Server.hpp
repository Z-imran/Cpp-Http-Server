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
