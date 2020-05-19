#include "EmptyCartException.h"

const char* EmptyCartException:: what() const noexcept(true){
    return "Cart is empty!";
}