#ifndef ITEMNOTINCARTEXCEPTION_H
#define ITEMNOTINCARTEXCEPTION_H

#include <exception>

using namespace std;


class ItemNotInCartException : public exception{

	public:
     const char* what() const noexcept(true);

};


#endif
