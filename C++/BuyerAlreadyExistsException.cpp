#include "BuyerAlreadyExistsException.h"

const char * BuyerAlreadyExistsException::what() const noexcept {
	return "Buyer already exists!";
}
