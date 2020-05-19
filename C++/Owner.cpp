#include "Owner.h"

Owner::Owner(string n, string m): User(n, m), isAdmin(true) {

}

bool Owner::getAdminStatus() {
    return this->isAdmin;
}

void Owner::changeAdminStatus() {
    this->isAdmin = this->isAdmin ? false : true;
}
