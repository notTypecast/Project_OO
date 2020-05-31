#ifndef BUYER_H
#define BUYER_H

#include "User.h"
#include "Item.h"
class ShoppingCart;

class Buyer: public User {
    public:

        enum CATEGORY {
            BRONZE,
            SILVER,
            GOLD
        };

        Buyer(string n, string m);

        ~Buyer();

        bool isOwner() override;

        void awardBonus(int points);

        void setBuyerCategory();

        void placeOrder(Item& item, int quantity);

        CATEGORY getBuyerCategory();

        string getBuyerCategoryString();

        int getBonus();

        ShoppingCart* getShoppingCart();

    private:
        int bonus;
        CATEGORY buyerCategory;
        ShoppingCart *cart;

        string enum_to_string[3];

};

#endif // BUYER_H
