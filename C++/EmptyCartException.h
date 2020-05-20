#ifndef EMPTYCARTEXCEPTION_H
#define EMPTYCARTEXCEPTION_H

#include <exception>

class EmptyCartException : public exception{
    public:
        const char* what() const noexcept(true);

};

#endif
