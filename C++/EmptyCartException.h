#ifndef EMPTYCARTEXCEPTION_H
#define EMPTYCARTEXCEPTION_H

#include <exception>

class EmptyCartException: public std::exception {
    public:
        const char* what() const noexcept;

};

#endif
