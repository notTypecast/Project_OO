#include "BadDataException.h"
#include <exception>

const char *BadDataException::what() const noexcept {
    return this->message.c_str();
}

BadDataException::BadDataException(std::string msg) : std::exception(), message(msg){}
