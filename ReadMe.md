# HTTP Server
- This project is a build of a http server in C++. We start of with building a basic server and creating the corresponding socket, binding it to ht eport, and marking it for listening. We then wait for a client to connect after which we parse the request, build a response adn send it back to the client which then closes the connection after receiving the response. 

### Goals
- The goal of the project is to develop a deeper understanding of how servers actually work while also developing a deeper understanding of how C++ works. 
- Familiarize myself with a deeper understanding of internet sockets, and handling requests. 
- Use asynchronous programming to be able to handle multiple client requests at once. 
- Its also just a cool project. 

### Technologies Used
- Cmake (build system)
- C++17
- POSIX Sockets


### ChangeLog
- Created basic Server that upon program run creates a socket and binds to the port and is set to listen. 
- Aded the ability for ther server to accept a client and recieve a request. 
- TODO: Add parsing of the request. <<EXPAND ON THE CHANGELOG LATER>>


### Bugs
- Upon making the build using Cmake on the first iteration of running the program the project works fine. However upon repeated attempts to run the project the server bind process fails which then closes the Program. Suggested fix: the error appears to be an address already in use case. So change the socket flag to be SO_REUSEADDR. (FIXED) Solution: use setsockopt to set the socket to reuse the port address instead of failing to bind. 

### Resources
Below are some resources used to help make programming easier. 
- https://man7.org/linux/man-pages/dir_section_2.html
- https://en.cppreference.com/w/cpp/header.html


