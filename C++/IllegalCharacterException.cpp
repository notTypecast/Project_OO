#include "IllegalCharacterException.h"

const char *IllegalCharacterException::what() const noexcept {
    return "Illegal character passed!";
}
