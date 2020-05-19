#include "InsufficientStockException.h"

const char* InsufficientStockException:: what() const noexcept(true){
    return "Not enough items in stock!";
}