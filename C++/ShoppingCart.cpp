#include "Menu.h"
#include "ShoppingCart.h"


ShoppingCart::ShoppingCart(){}

//throws exception when there aren't enough items in stock
void ShoppingCart::addItem(Item& item ,int q){
    int leftover_stock = item.getStock() - q;

    if(leftover_stock >= 0){
        item.setStock(leftover_stock);
        if (this->orderedItems.find(&item) != this->orderedItems.end())
            q += this->orderedItems[&item];
        this->orderedItems.erase(&item);
        this->orderedItems.insert({&item, q});

    }

    else
        throw InsufficientStockException();

}

void ShoppingCart::removeItem(Item& item){

    if(orderedItems.find(&item) == orderedItems.end())
            throw ItemNotInCartException();

    item.setStock(item.getStock() + orderedItems[&item]);
    orderedItems.erase(&item);

}

void ShoppingCart::editOrderedQuantity(Item& item , int newQ){

    if(this->orderedItems.find(&item) == orderedItems.end())
            throw ItemNotInCartException();

    int leftover_stock = item.getStock() + this->orderedItems[&item] - newQ;

    if(leftover_stock < 0)
            throw InsufficientStockException();

    else{
        item.setStock(leftover_stock);
        this->orderedItems.erase(&item);
        this->orderedItems.insert({&item, newQ});
    }

}

void ShoppingCart::showCart(Buyer::CATEGORY category){

    int i = 1;
    for (auto const& p: orderedItems) {
        cout << i << ". Item: " << p.first->getName() << ", price per unit: "
        << p.first->getPrice() << ", quantity: " << p.second << ", total price: "
        << p.first->getPrice() * p.second << endl;

        ++i;
    }

    if(i == 1)
        throw EmptyCartException();

    cout << "Total: " << this->calculateNet() <<endl;
    cout << "Courier cost: " << this->calculateCourierCost(category) << endl;
}

void ShoppingCart::clearCart(){

    for (auto it = this->orderedItems.cbegin(); it != this->orderedItems.cend(); ++it)
        this->removeItem(*it->first);

}

void ShoppingCart::checkout(Buyer& buyer){

    this->showCart(buyer.getBuyerCategory());

    bool checkout;

    Menu::getUserInput("Are you sure you would like to check out (y/n)? ", [this, &checkout](string ans){
        Menu::validateYesNoQuestion(ans);

        if (ans == "y")
            checkout = true;

        else if (ans == "n")
            checkout = false;
    });


    if (!checkout)
        return;

    int bonus = (int) (0.1 * this->calculateNet());

    buyer.awardBonus(bonus);

    this->orderedItems.clear();

    cout << "Checked out successfully!" << endl;
}

double ShoppingCart::calculateNet(){

    double total = 0.0;

    for(auto const&  key : orderedItems){
        total+= key.first->getPrice() * key.second;

    }

    return total;
}

double ShoppingCart::calculateCourierCost(Buyer::CATEGORY category){

    float modifier = 0.0f;
    double total;

    switch (category){
        case Buyer::CATEGORY::BRONZE :
            modifier = 1.0f;
            break;
        case Buyer::CATEGORY::SILVER:
            modifier = 0.5f;
            break;
        case Buyer::CATEGORY::GOLD:
            return 0.0;
    }

    total = this->calculateNet() * 0.02;

    if(total <3.0)
        total = 3.0;

    return total * modifier;
}

//getter for orderedItems

map<Item*,int> ShoppingCart::getOrderedItems() {
    return this->orderedItems;
}





