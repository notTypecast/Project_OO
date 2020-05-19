#include "ItemNotFoundException.h"

const char * ItemNotFoundException::what() const noexcept{
	return "Item not found!";
}
