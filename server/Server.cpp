#include "Server.hpp"
#include <iostream>
#include <unistd.h>         
#include <sys/socket.h>     
#include <netinet/in.h>     
#include <cstring>          


// Class implementation of the Server.hpp file.


Server::Server(int port) { 
    this->port = port;
    server_fd = -1;
    running = false; 
}

Server::~Server() {
    // Check if socket has been assigned if assigned close the socket.
    if (server_fd != -1) {
        close(server_fd);
        std::cout << "Closed Server Socket" << std::endl;
    }
}

bool Server::start() {
    return setUpSocket();
}

void Server::run() {
    return;
}

int Server::acceptClient() {
    return 0;
}

bool Server::setUpSocket() {
    // Assign server_fd to have a socket then check if the socket was created.
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket creation failed.\n";
        return false;
    }

    // We now bind the socket to the corresponding port number. 
    // First we clear the memory at the location (so nothing is misplaced)
    // Then we create a socket address which contains the port number(converted to network bytes), 
    // the corresponding protocol family(AF_INET), then we make the address for the socket biinding
    // to be INADDR_ANY (any addresss within the region). 
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); 
    addr.sin_addr.s_addr = INADDR_ANY;
    
    // If the Binding fails we exit the socket creation. 
    if (bind(server_fd, (sockaddr *) &addr, sizeof(addr)) == -1) {
        std::cerr << "Bind failed.\n";
        return false;
    }

    // We now set the corresponding socket to listen. 
    // If we fail to mark the socket as listening we fail. 
    if (listen(server_fd, 10) == -1) {
        std::cerr << "Listen failed.\n";
        return false;
    }

    // If we correctly create the socket, bind, and listen we can safely exit the function. 
    std::cout << "Server is sucessfully listening at port: " << port << "\n";
    running = true;
    return true;
    
}