#include "NoBuyersException.h"

const char * NoBuyersException::what() const noexcept {
	return "No registered buyers found!";
}
