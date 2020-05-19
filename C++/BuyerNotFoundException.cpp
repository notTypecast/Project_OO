#include "BuyerNotFoundException.h"

const char * BuyerNotFoundException::what() const noexcept {
	return "Buyer not found!";
}
