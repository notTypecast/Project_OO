#ifndef ILLEGALCHARACTEREXCEPTION_H
#define ILLEGALCHARACTEREXCEPTION_H

#include <exception>

class IllegalCharacterException: public std::exception {
    public:
        const char *what() const noexcept;
};

#endif // ILLEGALCHARACTEREXCEPTION_H
