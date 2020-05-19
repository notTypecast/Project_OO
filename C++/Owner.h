#include "User.h"
#ifndef OWNER_H
#define OWNER_H


class Owner: public User {
    private:
        bool isAdmin;

    public:
        Owner(string n, string m);

        bool getAdminStatus();

        void changeAdminStatus();

};

#endif // OWNER_H
