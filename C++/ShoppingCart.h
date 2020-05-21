#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <string>
#include <unordered_map>
#include "Buyer.h"
#include "Item.h"

using namespace std;


class ShoppingCart{

    private:
        unordered_map<Item*,int> orderedItems;


    public:

        ShoppingCart();

        void addItem(Item& item, int q);

        void removeItem(Item& item);

        void changeItemQuantity(Item& item , int newQ);

        void showCart(Buyer::CATEGORY category);

        void clearCart();

        void checkout(Buyer& buyer);

        double calculateNet();

        double calculateCourierCost(Buyer::CATEGORY category);

        unordered_map<Item*, int> getOrderedItems();

};

#endif

