#include "Menu.h"

Menu::Menu(EShop& eshop) : eshop(&eshop){
    this->emailRegex =new regex("^([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$");
};

Menu::~Menu(){
    delete this->emailRegex;
    delete this->usr;
    for (User* &bref: this->eshop->getBuyersList()){
        delete bref;
    }
}

string Menu::getUserInput(string msg, std::function<void(string)> validationFunc){
    string input;
    while (true) {
        cout << msg;
        getline(cin, input);

        if (validationFunc == NULL)
            break;

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

    string choice = Menu::getUserInput("Choose a category: ",[this](string choice){this->validateCategoryChoice(choice);});

    if (choice == "back")
        return;

    this->browseCategory(choice);

}

void Menu::browseCategory(string category){

    this->eshop->showProductsInCategory(category);

    string input = Menu::getUserInput("Item ID: ", [this](string choice){this->validateItemChoice(choice);});

    if (input == "back")
        return;

    int c = stoi(input);


    Item * chosenItem = this->eshop->getItemById(c);

    cout << chosenItem->toString() << endl;

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

    if (quantity_s == "back") {
        this->buyerPlaceOrder(chosenItem, category);
        return;
    }

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

    if (quantity_s == "back")
        return;

    int quantity = stoi(quantity_s);

    this->eshop->updateItemStock(chosenItem, quantity);

}

void Menu::ownerCheckStatus() {

    try {
        this->eshop->checkStatus();
    } catch(NoBuyersException e){
        cout << e.what() << endl;
        return;
    }

    string number = Menu::getUserInput("Select a buyer by number: ", [this](string number){this->validateBuyerNumber(number);});

    if (number == "back")
        return;

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
    map<Item *, int> allItems = cart.getOrderedItems();
    Item * chosenItem;
    string choice = Menu::getUserInput("Choose a product by number: ", [this, &chosenItem, allItems](string chc){
        transform(chc.begin(), chc.end(), chc.begin(), ::tolower);
        if (chc == "back"){
            this->viewCart();
            return;
        }
        this->validateOrderNumber(chc);
        int i =1;
        bool orderFoundFlag = false;
        int c = stoi(chc);
        for (auto const & p: allItems){
            if (i == c){
                orderFoundFlag = true;
                chosenItem = p.first;
                break;
            }
            ++i;
        }

        if (!orderFoundFlag){
            throw BadDataException("Choice out of range!");
        }
    });

    if (choice == "back")
        return;

    while (true) {

        choice = Menu::getUserInput("Delete or edit order: ", [this](string chc){this->validateEditDeleteChoice(chc);});

        if (choice == "edit"){
            string newq = Menu::getUserInput("New quantity: ", [this](string nq){this->validateItemQuantity(nq);});

            if (newq == "back")
                continue;

            int quant = stoi(newq);

            if (quant == 0)
                choice = "delete";

            else {
                try {
                    cart.editOrderedQuantity(*chosenItem, quant);
                }
                catch (InsufficientStockException ex){
                    cout << ex.what() << endl;
                }
            }
        }

        if (choice == "delete")
            cart.removeItem(*chosenItem);

        else if (choice == "back")
            this->editOrder(cart);

        break;

    }

}


void Menu::checkout() {

    Buyer* buyer = dynamic_cast<Buyer*>(this->usr);
    ShoppingCart* cart = buyer->getShoppingCart();

    try {
        cart->checkout(*buyer);
    }
    catch (EmptyCartException exc) {
        cout << exc.what() << endl;
    }

}


User* Menu::getMail() {

    User* newUser;
    string mail = Menu::getUserInput("E-mail address: ", [this](string address){this->validateEmailAddress(address);});

    try {
        newUser = this->eshop->authenticate(mail);
    }
    catch (UserNotFoundException exc) {
        string name;

        while (true) {

            try {
                name = Menu::getUserInput("User name: ");
                newUser = new Buyer(name, mail);
                break;
            }
            catch (InvalidNameLengthException exc) {
                cout << exc.what() << endl;
            }

        }
        this->eshop->addBuyer(newUser);

    }

    return newUser;

}


void Menu::runMenu() {
    this->commandsMap.clear();


    this->usr = this->getMail();
    if (this->usr->isOwner())
        this->ownerMenu();
    else
        this->buyerMenu();

}


void Menu::buyerMenu() {

    Buyer* buyer = dynamic_cast<Buyer*>(this->usr);

    cout << "Welcome, " << buyer->getName() << "!" << endl;
    cout << "Your e-mail address is " << buyer->getMail() << endl;
    cout << "Current bonus points: " << buyer->getBonus() << endl;
    cout << "Current buyer category: " << buyer->getBuyerCategoryString() << endl;

    this->commandsMap.insert({"browse", [this](){this->browse();}});
    this->commandsMap.insert({"view", [this](){this->viewCart();}});
    this->commandsMap.insert({"checkout", [this](){this->checkout();}});
    this->commandsMap.insert({"help", [this](){this->showHelp();}});
    this->commandsMap.insert({"logout", [this](){this->runMenu();}});
    this->commandsMap.insert({"exit", [this](){exit(0);}});

    this->runLoop();

}


void Menu::ownerMenu() {

    //cast to Owner* unnecessary, only User methods used

    cout << "Welcome, " << this->usr->getName() << "!" << endl;
    cout << "Your e-mail address is " << this->usr->getMail() << endl;
    cout << "You are the owner of the shop." << endl;

    this->commandsMap.insert({"browse", [this](){this->browse();}});
    this->commandsMap.insert({"status", [this](){this->ownerCheckStatus();}});
    this->commandsMap.insert({"help", [this](){this->showHelp();}});
    this->commandsMap.insert({"logout", [this](){this->runMenu();}});
    this->commandsMap.insert({"exit", [this](){exit(0);}});

    this->runLoop();

}


/* ------------
 * ------------
 *  INPUT VALIDATION METHODS
 *  -----------
 *  -----------
 */

void Menu::validateEmailAddress(string address) {

    if (!regex_match(address, *this->emailRegex))
        throw BadDataException("Insert a valid e-mail address!");

}


void Menu::validateEditDeleteChoice(string &chc){
    transform(chc.begin(), chc.end(), chc.begin(), ::tolower);

    if (!(chc == "edit" || chc == "delete" || chc=="back")){
        throw BadDataException("Expected delete or edit.");
    }

}

void Menu::validateOrderNumber(string chc){
    try {
        stoi(chc);
    } catch(...){
        throw BadDataException("Insert a valid integer!");
    }

}

void Menu::validateCartOptions(string& option) {
    transform(option.begin(), option.end(), option.begin(), ::tolower);

    if (!(option == "edit" || option == "clear" || option == "checkout" || option == "back"))
        throw BadDataException("Expected edit, clear or checkout.");

}

void Menu::validateBuyerNumber(string number) {
    transform(number.begin(), number.end(), number.begin(), ::tolower);
    if (number == "back")
        return;

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

    if ((quantity == "" && !this->usr->isOwner()) || quantity == "back")
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

    if (chc == "back")
        return;

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
        cout << "->" + row.first << endl;
    }
}

