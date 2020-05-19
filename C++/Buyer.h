#include "User.h"
#include "ShoppingCart.h"
#include "Item.h"
#ifndef BUYER_H
#define BUYER_H


class Buyer: public User {
    private:
        int bonus;
        CATEGORY buyerCategory;
        ShoppingCart *cart;


    public:
        Buyer(string n, string m);

        ~Buyer();

        void awardBonus(int points);

        void setBuyerCategory();

        void placeOrder(Item item, int quantity);

        CATEGORY getBuyerCategory();

        int getBonus();

        ShoppingCart getShoppingCart();

        enum CATEGORY {
            BRONZE,
            SILVER,
            GOLD
        }

};

#endif // BUYER_H
