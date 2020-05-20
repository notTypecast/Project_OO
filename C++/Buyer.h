#ifndef BUYER_H
#define BUYER_H

#include "User.h"
#include "ShoppingCart.h"
#include "Item.h"

class Buyer: public User {
    public:

        enum CATEGORY {
            BRONZE,
            SILVER,
            GOLD
        };

        Buyer(string n, string m);

        ~Buyer();

        void awardBonus(int points);

        void setBuyerCategory();

        void placeOrder(Item& item, int quantity);

        CATEGORY getBuyerCategory();

        int getBonus();

        ShoppingCart* getShoppingCart();

    private:
        int bonus;
        CATEGORY buyerCategory;
        ShoppingCart *cart;

};

#endif // BUYER_H
