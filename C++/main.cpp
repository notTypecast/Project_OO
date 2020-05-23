#include <iostream>
#include <vector>
#include <algorithm>
#include "User.h"
#include "Menu.h"
#include "EShop.h"
#include "Owner.h"
#include "Buyer.h"
#include "Item.h"
#include "Pen.h"
#include "Pencil.h"
#include "Notebook.h"
#include "Paper.h"

using namespace std;



int  main(){

    Owner owner("test", "test@mail.gr");
    EShop eshop("test_shop", owner);

    Item* items[12];
    Buyer* buyers[3];

    items[0] = new Pen("pen1", 10.5, "apple pen", 100, 12, "red", 10.76);

    items[1] = new Pen("pen2", 12, "pineapple pen", 14, 123, "blue", 10);

    items[2] = new Pen("pen3", 17, "Pen pineapple apple pen", 120, 200, "brown", 14);

    items[3] = new Pencil("Pencil1", 10.5, "Pencil 1", 100, 56, 12.5, Pencil::PENCIL_TYPE::H);

    items[4] = new Pencil("Pencil2", 13.5, "Pencil 2", 140, 356, 12.7, Pencil::PENCIL_TYPE::HB);

    items[5] = new Pencil("Pencil3", 0.5, "Pencil 3", 196, 66, 1.5, Pencil::PENCIL_TYPE::B);

    items[6] = new Notebook("notebook1", 4, "notebook 1", 100, 162, 3);

    items[7] = new Notebook("notebook2", 6, "notebook 2", 254, 54, 2);

    items[8] = new Notebook("notebook3", 2, "notebook 3", 653, 98, 5);

    items[9] = new Paper("Paper1", 3, "Paper 1", 67, 9898, 1223, 85);

    items[10] = new Paper("Paper2", 5, "Paper 2", 63, 98943, 1054, 66);

    items[11] = new Paper("Paper3", 9, "Paper 3", 623, 912, 1621, 55);


    buyers[0] = new Buyer("nick", "nick@mail.com");

    buyers[1] = new Buyer("chris", "chris@mail.com");

    buyers[2] = new Buyer("george", "george@mail.com");


    for (Item* i: items)
        eshop.addItem(*i);

    for (Buyer* b: buyers)
        eshop.addBuyer(dynamic_cast<User*>(b));

    buyers[0]->placeOrder(*items[1], 4);
    buyers[0]->placeOrder(*items[4], 2);
    buyers[0]->placeOrder(*items[8], 3);
    buyers[1]->placeOrder(*items[3], 2);
    buyers[1]->placeOrder(*items[10], 1);
    buyers[1]->placeOrder(*items[9], 2);
    buyers[2]->placeOrder(*items[2], 1);
    buyers[2]->placeOrder(*items[6], 3);
    buyers[2]->placeOrder(*items[11], 5);


    Menu menu(eshop);

    menu.runMenu();


    for (Item* i: items)
        delete i;

    for (Buyer* b: buyers)
        delete b;


}

