#ifndef EMPTYE_UNIQUE
#define EMPTYE_UNIQUE
#include <stdexcept>

class EmptyRequest : std::exception {
    public: 
    const char* what() const noexcept override {
        return "Request is empty.\n";
    }
};


#endif