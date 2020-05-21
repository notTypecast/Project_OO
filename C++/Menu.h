#ifndef MENU_H
#define MENU_H

#include "EShop.h"
#include "ShoppingCart.h"
#include "BadDataException.h"
#include "EmptyCartException.h"
#include "InsufficientStockException.h"
#include <regex>
#include <stdexcept>
#include <vector>
#include <functional>
#include <map>
#include <algorithm>

using namespace std;

class Menu
{
    public:
        Menu(EShop& eshop);
        static string getUserInput(string msg);
        static string getUserInput(string msg, function<void(string)> validationFunc);
        User * getMail();
        void runMenu();
        void buyerMenu();
        void ownerMenu(Owner &owner);
        ~Menu();

        static void validateYesNoQuestion(string& ans);

    private:
        EShop * eshop;
        User * usr;
        const regex * emailRegex;
        map <string, function<void()>> commandsMap;
        void runLoop();
        void browse();
        void browseCategory(string category);
        void buyerPlaceOrder(Item &chosenItem, string category);
        void ownerEditItem(Item &chosenItem, string category);
        void ownerCheckStatus();
        void ownerBuyerOptions(Buyer &buyer, int c);
        void viewCart();
        void editOrder(ShoppingCart &cart);
        void checkout();

        void showHelp();
        void validateCommand(string command);
        void validateCategoryChoice(string& chc);
        void validateItemChoice(string chc);
        void validateItemQuantity(string quantity);
        void validateBuyerNumber(string number);
        void validateCartOptions(string& option);
        void validateOrderNumber(string chc);
        void validateEditDeleteChoice(string &chc);

};

#endif // MENU_H
