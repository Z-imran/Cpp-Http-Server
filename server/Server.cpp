#include "Server.hpp"
#include <iostream>
#include <unistd.h>         
#include <sys/socket.h>     
#include <netinet/in.h>     
#include <cstring>          
#include <arpa/inet.h>
#include "Request.hpp"
#include "Exceptions/EmptyException.hpp"
#include "Exceptions/MalformedException.hpp"

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
    //main loop which runs while running is set to true.
    while (running) {
        // block unitl we accept a client or get an error
        int client_fd = acceptClient();
        if (client_fd == -1) {
            std::cerr << "Connectin failed.\n";
            continue; 
        }


        // At this point we are guaranteed client connection so we should print a quick message. 
        std::cout << "Client successfully connected at FD: " << client_fd << "\n";

        // We must now recieve the request from the client. For now we will hard cap the limit 
        // of the request to be  4096 bytes long but we can later change this or we can use a loop. 
        char str[4096];

        // If the recieve failed we should print an error message and then close the connection. 
        // Else we should print out the client request so we can see what it loooks like. 
        // We use a while loop to make sure that the entire request is recieved without any issues. 
        int bytes;
        std::string raw_request;
        do {
            bytes = recv(client_fd, &str, 4096, 0);

            // If the recv produced an error break the loop. 
            if (bytes == -1) {
            std::cerr << "unable to recieve request.\n";
            break;
            } 
            raw_request.append(str);

            // If the string has reached the end exit the loop.
            if (raw_request.find("\r\n\r\n") != std::string::npos) {
                break;
            }

        } while (bytes > 0);

        // Should the request string be empty for some reason the connection should be closed. 

        std::cout << "Client Request: " << raw_request << "\n";
        Request parsed_request;
        try {
            parsed_request = parseRequest(raw_request);
        } catch(const EmptyRequest& e) {
            std::cerr << e.what();
            close(client_fd);
            continue;
        } catch(const MalformedRequest& e) {
            std::cerr << e.what();
            close(client_fd);
            continue;
        }
        std::cout << parsed_request.method << "\n";
        std::cout << parsed_request.path << "\n";
        std::cout << parsed_request.version << "\n";
        for (const std::pair<const std::string, std::string>& pair : parsed_request.headers) {
            std::cout << pair.first << ": " << pair.second << "\n";
        }
        std::cout << parsed_request.body << "\n";

        // Close client connection for now.
        close(client_fd);
        std::cout << "Closed client connection.\n";
    }
}

int Server::acceptClient() {
    // accept() blocks until we recieve a client in the queue to which we can build a connection.
    sockaddr_in addr; 
    socklen_t len = sizeof(addr);
    int client_fd = accept(server_fd, (sockaddr *) &addr, &len);

    // If the connection failed send an error message
    if (client_fd == -1) {
        std::cerr << "Connection failed.\n";
        return -1;
    }

    // Print the clients IP 
    char str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN);
    std::cout << "Accepted client connection from: " << str << "\n";
    return client_fd;
}

bool Server::setUpSocket() {
    // Assign server_fd to have a socket then check if the socket was created.
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Socket creation failed.\n";
        return false;
    }

    // Set the socket to use the flag SO_REUSEADDR so we dont have issues with the port number binding. 
    int optval = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); 

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
        std::cerr << "Bind failed.\n" << "Error No: " << errno << " : " << strerror(errno) << "\n";
        perror("bind");
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

Response Server::handleRequest(const Request& req) {
    return Response();
}