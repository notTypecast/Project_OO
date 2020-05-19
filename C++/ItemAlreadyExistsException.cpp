#include "ItemAlreadyExistsException.h"

const char * ItemAlreadyExistsException::what() const noexcept {
	return "Item already exists!";
}
