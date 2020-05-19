#include "ItemNotInCartException.h"

const char* ItemNotInCartException :: what() const noexcept(true){
    return "That item is not in the cart!";
}