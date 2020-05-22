#include "User.h"

User::User(string n, string m): name(n), mail(m) {

    if (!(n.length() > 2 && n.length() < 20))
        throw InvalidNameLengthException();

}

string User::getName() {
    return this->name;
}

void User::setName(string n) {
    this->name = n;
}

string User::getMail() {
    return this->mail;
}

void User::setMail(string m) {
    this->mail = m;
}
