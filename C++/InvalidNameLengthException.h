#ifndef INVALIDNAMELENGTHEXCEPTION_H
#define INVALIDNAMELENGTHEXCEPTION_H

#include <exception>

class InvalidNameLengthException: public std::exception {
    public:
        const char *what() const noexcept;
};

#endif // INVALIDNAMELENGTHEXCEPTION_H
