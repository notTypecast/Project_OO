#include <exception>

using namespace std;

#ifndef EMPTYCARTEXCEPTION_H
#define EMPTYCARTEXCEPTION_H

class EmptyCartException : public exception{
    public:
        const char* what() const noexcept(true);

};

#endif