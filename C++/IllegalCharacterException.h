#include <exception>
#ifndef ILLEGALCHARACTEREXCEPTION_H
#define ILLEGALCHARACTEREXCEPTION_H


class IllegalCharacterException: public std::exception {
    public:
        const char *what() const noexcept;
};

#endif // ILLEGALCHARACTEREXCEPTION_H
