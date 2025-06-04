#include <iostream>
#include "server/Server.hpp"


int main() {
    std::cout << "Hello World, Beginning server creation" << std::endl;
    
    // Construct a server (not mallocated)
    Server server(8080);

    // If Server fails to start produce an err message and exit. 
    if (!server.start()) {
        std::cerr << "Server failed to start ... Exiting the Program.\n";
        return 1;
    }

    std::cout << "Server setup complete ... Running the Program.\n";

    server.run();
}