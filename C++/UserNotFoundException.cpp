#include "UserNotFoundException.h"

const char* UserNotFoundException::what() const noexcept {
	return "User not found!";
}
