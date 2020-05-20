#include "EShop.h"

using namespace std;

/* -------------------
 * -------------------
 *  NOTE: should we change some methods to const?
 *  ------------------
 *  ------------------
 */

EShop::EShop(string name, Owner * &owner) : name(name), owner(owner){}

void EShop::addItem(Item * item){

	for (Item * &iptr : this->itemsVec){
		if (iptr->getId() == item->getId()){
			throw ItemAlreadyExistsException();
		}
	}

	this->itemsVec.push_back(item);
}


Item * EShop::getItemById(int id){

	for (Item * &iptr : this->itemsVec){
		if (iptr->getId() == id){
			return iptr;
		}
	}

	throw ItemNotFoundException();

}




void EShop::removeItem(Item * i){
	
	vector<Item *>::iterator it = this->itemsVec.begin();
	bool itemFoundFlag = false;

	while (it != this->itemsVec.end()) {

		if ((*it)->getId() == i->getId()){

			delete *it;
			it = this->itemsVec.erase(it);
			itemFoundFlag = true;
			break;

		} else {
			++it;
		}
	}

	if (!itemFoundFlag){
		throw ItemNotFoundException();
	}

}


void EShop::addBuyer(User * b){

	for (User * &bref: this->buyersVec){
		if (bref->getMail() == b->getMail()){
			throw BuyerAlreadyExistsException();
		}
	}




	this->buyersVec.push_back(b);

	

}


void EShop::removeBuyer(User * b){
	vector <User *>::iterator it = this->buyersVec.begin();
	bool buyerFoundFlag = false;

	while (it != this->buyersVec.end()) {

		if (b->getMail().compare((*it)->getMail()) == 0){

			delete *it;
			it = this->buyersVec.erase(it);
			buyerFoundFlag = true;
			break;

		} else {
			++it;
		}
	}

	if (!buyerFoundFlag){
		throw BuyerNotFoundException();
	}	
}


void EShop::updateItemStock(Item * item, int stock){

	for (Item * &iptr : this->itemsVec){
		if (iptr->getId() == item->getId()){
			
			item->setStock(stock);
			cout << "Successfully updated stock of item with ID "	<< item->getId() << ".";
			return;
		}
	}

	throw ItemNotFoundException();



}


vector <string> EShop::getCategories(){
	vector <string> tempVec;

	for (Item * &iptr : this->itemsVec){
		string currentCategory = iptr->getCategory();
		bool categoryExists = false;


		for (string &strref : tempVec){
			if (currentCategory.compare(strref) == 0){
				categoryExists = true;
				break;
			}
		}

		if (!categoryExists){
			tempVec.push_back(currentCategory);
		}

	}


	return tempVec;
}


void EShop::showCategories(){
	cout << "------" << endl;
	cout << "Available categories: " << endl;

	for (string strref: this->getCategories()){
		string currentCategory = strref;

		currentCategory[0] = toupper(currentCategory[0]);

		cout << currentCategory << endl;
	}

}

void EShop::showProductsInCategory(string category){

	// converting given category to lower case
	transform(category.begin(), category.end(), category.begin(), ::tolower);

	cout << "------" << endl;
	cout << "Showing available items in category: " << category << endl;

	for (Item * &iptr: this->itemsVec){
		cout << iptr->toString() << endl;
	}

	cout << "------" << endl;

}

void EShop::showProduct(Item * product){
	cout << product->toString() << endl;
}

void EShop::checkStatus(){

	int maxlen_name = 0;

	for (User * &bref: this->buyersVec){
		if (maxlen_name < bref->getName().length()){
			maxlen_name = bref->getName().length();
		}
	}

	maxlen_name += 4;

	cout << "No\tName";
	for (int i=0; i<maxlen_name -6; ++i){
		cout << " ";
	}
	cout << "Points\tCategory" << endl; 

	cout << "---------------------------------------" << endl;
	int count = 1;
	for (User * &bref: this->buyersVec){
		cout << count++ << "\t" << bref->getName();

		for (int i=0; i< maxlen_name - bref->getName().length(); ++i){
			cout << " ";
		}

		cout << (dynamic_cast<Buyer *>(bref))->getBonus() << "\t" << (dynamic_cast<Buyer *>(bref))->getBuyerCategory() << endl;

	}

	cout << "---------------------------------------" << endl;

}


User * EShop::authenticate(string mail){

	if (mail.compare(this->owner->getMail()) == 0) {

		return this->owner;

	} else {

		for (User * &bref : this->buyersVec){
			if (mail.compare(bref->getMail())){
				return bref;
			}
		}

	}

}


string EShop::getName(){
	return this->name;
}

vector <User *> EShop::getBuyersList(){
	return this->buyersVec;
}	
