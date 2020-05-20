#ifndef ITEMALREADYEXISTSEXCEPTION_H
#define ITEMALREADYEXISTSEXCEPTION_H

#include <exception>

class ItemAlreadyExistsException : public std::exception {
	public:
		const char * what() const noexcept ;
};


#endif
