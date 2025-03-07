#ifndef ITEMNOTFOUNDEXCEPTION_H
#define ITEMNOTFOUNDEXCEPTION_H
#include <exception>

class ItemNotFoundException : public std::exception {
	public: 
		const char * what() const noexcept;
};

#endif
