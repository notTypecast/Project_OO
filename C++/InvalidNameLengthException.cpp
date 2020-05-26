#include "InvalidNameLengthException.h"

const char* InvalidNameLengthException:: what() const noexcept{
    return "Name should be between 3 and 19 characters.";
}
