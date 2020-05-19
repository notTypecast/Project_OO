#include <exception>
#ifndef BUYERALREADYEXISTSEXCEPTION_H
#define BUYERALREADYEXISTSEXCEPTION_H

class BuyerAlreadyExistsException : public std::exception {
	const char * what() const noexcept;
};



#endif
