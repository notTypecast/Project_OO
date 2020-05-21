#ifndef BUYERNOTFOUNDEXCEPTION_H
#define BUYERNOTFOUNDEXCEPTION_H

#include <exception>

class BuyerNotFoundException : public std::exception {
	public: 
		const char * what() const noexcept;
};

#endif
