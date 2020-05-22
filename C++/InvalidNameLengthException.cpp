#include "InvalidNameLengthException.h"

const char* InvalidNameLengthException:: what() const noexcept{
    return "Name should be between 2 and 20 characters.";
}
