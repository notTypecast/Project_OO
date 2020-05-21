#ifndef MENU_H
#define MENU_H

#include "EShop.h"
#include "BadDataException.h"
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

		private:
				EShop * eshop;
				User * usr;
				const regex * emailRegex;
				map <string, function<void()>> commandsMap;
				void runLoop();
				void browse();
				void browseCategory(string choice);
				void buyerPlaceOrder(Item &chosenItem, string choice);
				void ownerEditItem(Item &chosenItem, string choice);
				void ownerCheckStatus();
				void ownerBuyerOptions(Buyer &buyer, int c);
				void viewCart();
				void editOrder(ShoppingCart &cart);
				void checkout();

				void validateCommand(string command);
				void showHelp();
				void validateCategoryChoice(string chc);
				void validateItemChoice(string chc);

};

#endif // MENU_H
