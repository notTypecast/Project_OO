#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <string>
#include <map>
#include <iostream>
#include "Buyer.h"
#include "Item.h"
#include "InsufficientStockException.h"
#include "ItemNotInCartException.h"
#include "EmptyCartException.h"


using namespace std;


class ShoppingCart{

    private:
        map<Item*,int> orderedItems;


    public:

        ShoppingCart();

        void addItem(Item& item, int q);

        void removeItem(Item& item);

        void editOrderedQuantity(Item& item , int newQ);

        void showCart(Buyer::CATEGORY category);

        void clearCart();

        void checkout(Buyer& buyer);

        double calculateNet();

        double calculateCourierCost(Buyer::CATEGORY category);

        map<Item*, int> getOrderedItems();

};

#endif

