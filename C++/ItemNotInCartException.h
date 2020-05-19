#include <exception>

using namespace std;

#ifndef ITEMNOTINCARTEXCEPTION_H
#define ITEMNOTINCARTEXCEPTION_H

class ItemNotInCartException : public exception{

     const char* what() const noexcept(true);
     
};


#endif