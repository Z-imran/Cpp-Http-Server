#ifndef MALFORMEDE_UNIQUE
#define MALFORMEDE_UNIQUE
#include <stdexcept>

class MalformedRequest : std::exception {
    public: 
    const char* what() const noexcept override {
        return "Request is malformed.\n";
    }
};


#endif