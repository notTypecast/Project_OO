#ifndef USERNOTFOUNDEXCEPTION_H
#define USERNOTFOUNDEXCEPTION_H


#include <exception>

class UserNotFoundException: public std::exception {
	public:
		const char * what() const noexcept;
};


#endif // USERNOTFOUNDEXCEPTION_H
