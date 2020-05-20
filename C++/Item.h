#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <sstream>
#include <iostream>

using namespace std;


class Item {
    private:

        string name;
        double price;
        string description;
        int stock;
        int id;

    public:

        Item(string n, double p, string d, int s, int i);

        string getBasicInfo();

        virtual string getDetails() = 0;

        virtual string getCategory() = 0;

        string toString();

        void setName(string n);

        void setPrice(double p);

        void setDescription(string d);

        void setStock(int s);

        string getName();

        double getPrice();

        int getStock();

        int getId();



};

#endif // ITEM_H
