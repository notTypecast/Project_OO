#include "InsufficientStockException.h"

const char* InsufficientStockException:: what() const noexcept{
    return "Not enough items in stock!";
}
