#include <exception>
#ifndef ITEMALREADYEXISTSEXCEPTION_H
#define ITEMALREADYEXISTSEXCEPTION_H

class ItemAlreadyExistsException : public std::exception {
	public:
		const char * what() const noexcept ;
};


#endif
