#ifndef NOBUYERSEXCEPTION_H
#define NOBUYERSEXCEPTION_H

#include <exception>

class NoBuyersException : public std::exception {
	public:
		const char * what() const noexcept ;
};


#endif
