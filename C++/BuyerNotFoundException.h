#include <exception>
#ifndef BUYERNOTFOUNDEXCEPTION_H
#define BUYERNOTFOUNDEXCEPTION_H


class BuyerNotFoundException : public std::exception {
	const char * what() const noexcept;
};

#endif
