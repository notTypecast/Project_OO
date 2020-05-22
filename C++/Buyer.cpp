#include "Buyer.h"
#include "ShoppingCart.h"

Buyer::Buyer(string n, string m): User(n, m), bonus(0) {
    this->cart = new ShoppingCart();

    this->setBuyerCategory();

    this->enum_to_string[0] = "BRONZE";
    this->enum_to_string[1] = "SILVER";
    this->enum_to_string[2] = "GOLD";
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

string Buyer::getBuyerCategoryString() {
    return this->enum_to_string[this->buyerCategory];
}

int Buyer::getBonus() {
    return this->bonus;
}

ShoppingCart* Buyer::getShoppingCart() {
    return this->cart;
}

