#ifndef OWNER_H
#define OWNER_H

#include "User.h"

class Owner: public User {
    private:
        bool isAdmin;

    public:
        Owner(string n, string m);

        bool isOwner() override;

        bool getAdminStatus();

        void changeAdminStatus();

};

#endif // OWNER_H
