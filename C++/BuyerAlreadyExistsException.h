#ifndef BUYERALREADYEXISTSEXCEPTION_H
#define BUYERALREADYEXISTSEXCEPTION_H

#include <exception>

class BuyerAlreadyExistsException : public std::exception {
	public: 
		const char * what() const noexcept;
};



#endif
