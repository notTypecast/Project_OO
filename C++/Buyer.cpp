#include "Buyer.h"
#include "ShoppingCart.h"

Buyer::Buyer(string n, string m): User(n, m), bonus(0) {
    this->cart = new ShoppingCart();

    this->setBuyerCategory();
}

Buyer::~Buyer() {
    delete this->cart;
}

bool Buyer::isOwner() {
    return false;
}

void Buyer::awardBonus(int points) {
    this->bonus += points;

    this->setBuyerCategory();
}

void Buyer::setBuyerCategory() {
    if (this->bonus > 200)
        this->buyerCategory = CATEGORY::GOLD;
    else if (this->bonus > 100)
        this->buyerCategory = CATEGORY::SILVER;
    else
        this->buyerCategory = CATEGORY::BRONZE;
}

void Buyer::placeOrder(Item& item, int quantity) {
    this->cart->addItem(item, quantity);
}

Buyer::CATEGORY Buyer::getBuyerCategory() {
    return this->buyerCategory;
}

int Buyer::getBonus() {
    return this->bonus;
}

ShoppingCart* Buyer::getShoppingCart() {
    return this->cart;
}

