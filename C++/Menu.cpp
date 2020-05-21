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


}


/* ------------
 * ------------
 *  INPUT VALIDATION METHODS
 *  -----------
 *  -----------
 */

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


void Menu::validateCategoryChoice(string chc) {
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

void Menu::showHelp(){
	cout << "Available commands: " << endl;
	for (auto const &row: this->commandsMap){
		cout << "->" + row.first;
	}
}





