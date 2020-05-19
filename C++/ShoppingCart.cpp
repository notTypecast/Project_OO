#include <iostream>
#include <exception>
#include "ShoppingCart.h"
#include "InsufficientStockException.h"
#include "ItemNotInCartException.h"
#include "EmptyCartException.h"
#include "Menu.h"


ShoppingCart::ShoppingCart(){}

//throws exception when there aren't enough items in stock
void ShoppingCart::addItem(Item& item ,int q){
    int leftover_stock = item.getStock() - q;

    if(leftover_stock >= 0){
        item.setStock(leftover_stock);
        this->orderedItems.insert(make_pair(&item,q));

    }

    else{ 

        try{
            throw InsufficientStockException();
        }

        catch(exception& e){
            cout << e.what() << endl;
        }
    }

}

void ShoppingCart::removeItem(Item& item){

    if(orderedItems.find(&item) == orderedItems.end()){
        
        try{
            throw ItemNotInCartException();
        }
        catch(exception& ex){
            cout<< ex.what() <<endl;
        }
    }

    else{
        item.setStock(item.getStock() + orderedItems[&item]);
        orderedItems.erase(&item);
    }
    
}

void ShoppingCart :: changeItemQuantity(Item& item , int newQ){
    int leftover_stock = item.getStock() - newQ;

    if(orderedItems.find(&item) == orderedItems.end()){
        
        try{
            throw ItemNotInCartException();
        }
        catch(exception& ex){
            cout<< ex.what() <<endl;
        }
    }

    else if(leftover_stock < 0){

         try{
            throw InsufficientStockException();
        }

        catch(exception& e){
            cout << e.what() << endl;
        }

    }

    else{
        item.setStock(leftover_stock);
        orderedItems.erase(&item);
        this->orderedItems.insert(make_pair(&item,newQ));
    }

}

void ShoppingCart::showCart(Buyer::CATEGORY category){
    
    int i =1
    for(auto& key : orderedItems){
        cout << i << ". Item: " << key.first->getName() << ", price per unit: " 
        << key.first->getPrice() << ", quantity: " << key.second << ", total price: " 
        << key.first->getPrice() * key.second << endl;

        ++i;    
    }

    if(i == 1){
        try{
            throw EmptyCartException();
        }
        catch(exception& e1){
            cout << e1.what() << endl;
        }
    }

    cout << "Total: " << this->calculateNet() <<endl;
    cout << "Courier cost: " << this->calculateCourierCost(category) << endl;
} 

void ShoppingCart::clearCart(){

    for(auto& key : orderedItems){
        
        this->removeItem(*(key.first));
    
    }
}

void ShoppingCart::checkout(Buyer& buyer){

    this->showCart(buyer.getBuyerCategory());

    //get answer
    while(true){
        String ans = toLower(Menu::getUserInput("Are you sure you would like to check out (y/n)? "));

        if(ans.compare("y") == 0) 
            break;
        
        else if(ans.compare("n") == 0) 
            return;

        else 
            cout << "Expected y/n" << endl;

    }

    int bonus = (int) (o.1 * this->calculateNet());

    buyer.awardBonus(bonus);

    this->orderedItems.clear();

    cout << "Checked out successfully!" << endl;
}

double ShoppingCart::calculateNet(){

    double total = 0.0;

    for(auto& key : orderedItems){
        total+= key.first->getPrice() * key.second;

    }

    return total;
}

double ShoppingCart::calculateCourierCost(Buyer::Category category){

    float modifier = 0.0f;
    double total;

    switch (category){
        case BRONZE :
            modifier = 1.0f;
            break;
        case SILVER:
            modifier = 0.5f;
            break;
        case GOLD:
            return 0.0;
    }

    total = this->calculateNet() * 0.02;

    if(total <3.0)
        total = 3.0;
    
    return total * modifier;
}

//getter for orderedItems

unordered_map<Item*,int> getOrderedItems({
    return this->orderedItems;
}





