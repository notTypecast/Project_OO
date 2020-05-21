#include "Menu.h"

Menu::Menu(EShop& eshop) : eshop(&eshop){
	this->emailRegex =new regex("^([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$");
};

Menu::~Menu(){
	delete this->emailRegex;
	delete this->usr;
}

string Menu::getUserInput(string msg, std::function<void(string)> validationFunc){
	string input;
	while (true) {
		cout << msg;
		cin >> input;

		if (validationFunc == NULL){
			break;
		}

		try {
			validationFunc(input);
			break;
		} catch (BadDataException ex){
			cout << ex.what() << endl;
		}


	}

	return input;
}



string Menu::getUserInput(string msg){
	return Menu::getUserInput(msg, NULL);
}




void Menu::runLoop(){
	string command;

	while (true){
		command = Menu::getUserInput(">> ", [this](string cmd){this->validateCommand(cmd);});
		commandsMap[command]();
	}

}

void Menu::browse(){
	cout << "Shop name: " + this->eshop->getName() << endl;
	this->eshop->showCategories();

	string choice = getUserInput("Choose a category: ",[this](string choice){this->validateCategoryChoice(choice);} );

	this->browseCategory(choice);

}

void Menu::browseCategory(string category){

	this->eshop->showProductsInCategory(category);

	int c = stoi(getUserInput("Item ID: ", [this](string choice){this->validateItemChoice(choice);}));

    Item * chosenItem = this->eshop->getItemById(c);

    cout << chosenItem->toString();

    if (this->usr->isOwner())
        this->ownerEditItem(*chosenItem, category);
    else
        this->buyerPlaceOrder(*chosenItem, category);

}

void Menu::buyerPlaceOrder(Item& chosenItem, string category) {

    bool confirmPlaceOrder;

    Menu::getUserInput("Would you like to place an order for this item (y/n)? ", [this, &confirmPlaceOrder, category](string ans){
        Menu::validateYesNoQuestion(ans);

        if (ans == "y")
            confirmPlaceOrder = true;

        else if (ans == "n")
            confirmPlaceOrder = false;

        //return unnecessary, function exits anyway after back
        else
            this->browseCategory(category);
    });

    if (!confirmPlaceOrder)
        return;


    string quantity_s = Menu::getUserInput("Quantity (blank for 1): ", [this](string quantity){this->validateItemQuantity(quantity);});
    int quantity;

    if (quantity_s == "")
        quantity = 1;
    else
        quantity = stoi(quantity_s);


    if (quantity != 0) {

        Buyer* buyer = dynamic_cast<Buyer*>(this->usr);

        try {
            buyer->placeOrder(chosenItem, quantity);
        }
        catch (InsufficientStockException exc) {
            cout << exc.what() << endl;
        }

    }


}

void Menu::ownerEditItem(Item& chosenItem, string category) {

    string quantity_s = Menu::getUserInput("Enter new quantity: ", [this, category](string quantity){
        transform(quantity.begin(), quantity.end(), quantity.begin(), ::tolower);
        if (quantity == "back")
            this->browseCategory(category);
        else
            this->validateItemQuantity(quantity);
    });
    int quantity = stoi(quantity_s);

    this->eshop->updateItemStock(chosenItem, quantity);

}

void Menu::ownerCheckStatus() {

    this->eshop->checkStatus();

    string number = Menu::getUserInput("Select a buyer by number: ", [this](string number){this->validateBuyerNumber(number);});
    int n = stoi(number);


    try {
        this->ownerBuyerOptions(*dynamic_cast<Buyer*>(this->eshop->getBuyersList().at(n - 1)), n);
    }
    catch (out_of_range) {
        cout << "No buyer has that number!" << endl;
    }

}


void Menu::ownerBuyerOptions(Buyer& buyer, int c) {

    try {
        buyer.getShoppingCart()->showCart(buyer.getBuyerCategory());
    }
    catch (EmptyCartException exc) {
        cout << exc.what() << endl;
    }

    bool removeBuyer;

    Menu::getUserInput("Would you like to remove this buyer (y/n)? ", [this, &removeBuyer](string ans) {
        Menu::validateYesNoQuestion(ans);

        if (ans == "y")
            removeBuyer = true;

        else if (ans == "n")
            removeBuyer = false;

        else
            this->ownerCheckStatus();
    });

    if (removeBuyer)
        this->eshop->removeBuyer((User *) &buyer);

}


void Menu::viewCart() {

    Buyer* buyer = dynamic_cast<Buyer*>(this->usr);
    ShoppingCart* cart = buyer->getShoppingCart();

    try {
        cart->showCart(buyer->getBuyerCategory());
    }
    catch (EmptyCartException exc) {
        cout << exc.what() << endl;
        return;
    }

    string option = Menu::getUserInput("Edit order, clear cart or checkout (edit, clear, checkout): ", [this](string option){this->validateCartOptions(option);});

    if (option == "edit")
        this->editOrder(*buyer->getShoppingCart());
    else if (option == "clear")
        buyer->getShoppingCart()->clearCart();
    else if (option == "checkout")
        this->checkout();

}


void Menu::editOrder(ShoppingCart& cart) {

}


void Menu::checkout() {

}


/* ------------
 * ------------
 *  INPUT VALIDATION METHODS
 *  -----------
 *  -----------
 */

void Menu::validateCartOptions(string& option) {
    transform(option.begin(), option.end(), option.begin(), ::tolower);

    if (!(option == "edit" || option == "clear" || option == "checkout" || option == "back"))
        throw BadDataException("Expected edit, clear or checkout.");

}

void Menu::validateBuyerNumber(string number) {
    transform(number.begin(), number.end(), number.begin(), ::tolower);
    if (number == "back") {
        this->runLoop();
        return;
    }

    int n;

    try {
        n = stoi(number);
        if (n <= 0)
            throw new BadDataException("Choice out of range!");
    }
    catch (...) {
        throw BadDataException("Please enter a valid integer.");
    }


}


 void Menu::validateItemQuantity(string quantity) {

    if (quantity == "" && !this->usr->isOwner())
        return;

    int c;
    try {
        c = stoi(quantity);
        if (c < 0)
            throw BadDataException("Choice out of range!");
    }
    catch (...) {
        throw BadDataException("Insert a valid quantity!");
    }


 }


void Menu::validateItemChoice(string chc){
	transform(chc.begin(), chc.end(), chc.begin(), ::tolower);
	if (chc == "back"){
		browse();
		return;
	}
	int c;

	try {
		c = stoi(chc);
		this->eshop->getItemById(c);
	}
	catch (ItemNotFoundException ex) {
        throw BadDataException(ex.what());
	}
	catch (...){
        throw BadDataException("Insert a valid ID!");
	}

}


void Menu::validateCategoryChoice(string& chc) {
	transform(chc.begin(), chc.end(), chc.begin(), ::tolower);

	if (chc == "back"){
		runLoop();
		return;
	}

	vector <string> categories= this->eshop->getCategories();

	if (find(categories.begin(), categories.end(), chc) != categories.end()){
		return;
	}

	throw BadDataException("Unknown category!");


}


void Menu::validateCommand(string command){
	for (auto const &row : this->commandsMap){
		if (row.first == command){
			return;
		}
	}

	throw BadDataException("Unknown command! Use >>help for a list of available commands.");
}


void Menu::validateYesNoQuestion(string& ans) {
    transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
    if (!(ans == "y" || ans == "n" || ans == "back"))
        throw BadDataException("Expected y/n.");

}


void Menu::showHelp(){
	cout << "Available commands: " << endl;
	for (auto const &row: this->commandsMap){
		cout << "->" + row.first;
	}
}





