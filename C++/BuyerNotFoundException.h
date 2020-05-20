#ifndef BUYERNOTFOUNDEXCEPTION_H
#define BUYERNOTFOUNDEXCEPTION_H

#include <exception>

class BuyerNotFoundException : public std::exception {
	const char * what() const noexcept;
};

#endif
