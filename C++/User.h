#include <string>

using namespace std;

#ifndef USER_H
#define USER_H

class User {

    private:
        string name;
        string mail;


    public:
        User(string n, string m);
        virtual ~User() = default;

        string getName();
        void setName(string n);
        string getMail();
        void setMail(string m);

};

#endif // USER_H
