#include <exception>

using namespace std;


#ifndef INSUFFICIENTSTOCKEXCEPTION_H
#define INSUFFICIENTSTOCKEXCEPTION_H

class InsufficientStockException : public exception{

    public:
        const char* what() const noexcept;

};

#endif
