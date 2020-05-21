#ifndef ESHOP_H
#define ESHOP_H

#include <iostream>
#include <cctype>
#include <algorithm>
#include <iterator>
#include "ItemAlreadyExistsException.h"
#include "ItemNotFoundException.h"
#include "BuyerAlreadyExistsException.h"
#include "BuyerNotFoundException.h"
#include "Buyer.h"
#include "User.h"
#include <vector>
#include "Item.h"
#include "Owner.h"

using namespace std;

class EShop {

	private:
		string name;
		Owner owner;
		vector <Item *> itemsVec;
		vector <User *> buyersVec;

	public:
		EShop(string name, Owner &owner);
		void addItem(Item &i);
		Item * getItemById(int id);
		void removeItem(Item &i);
		void addBuyer(User* b);
		void removeBuyer(User* b);
		void updateItemStock(Item &item, int stock);
		void showCategories();
		void showProductsInCategory(string category);
		void showProduct(Item &product);
		void checkStatus();
		User * authenticate(string mail);
		string getName();
		vector <string> getCategories();
		vector <User *> getBuyersList();




};

#endif
