#ifndef BADDATAEXCEPTION_H
#define BADDATAEXCEPTION_H
#include <exception>
#include <string>

class BadDataException : public std::exception {
	private:
		std::string message;
	public: 
		BadDataException(std::string msg);
		const char *what() const noexcept;
};


#endif
