#include "Item.h"
#include "IllegalCharacterException.h"

Item::Item(string n, double p, string d, int s, int i): name(n), price(p), description(d), stock(s), id(i) {

    if (n.find(";") != string::npos || d.find(";") != string::npos)
        throw IllegalCharacterException();

}

string Item::getBasicInfo() {

    return this->name + ";" + to_string(this->price) + ";" + this->description + ";" + to_string(this->stock) + ";" + to_string(this->id);

}

string Item::toString() {

    string data[5];

    string initial = this->getBasicInfo();
    stringstream input_sstream(initial);

    for (int i = 0; i < 5; ++i)
        getline(input_sstream, data[i], ';');

    return "Item name: " + data[0] + ", Price: " + data[1] + ", Description: " + data[2] + ", Stock: " + data[3] + ", ID: " + data[4] + this->getDetails();

}

void Item::setName(string n) {

    if (n.find(";") != string::npos)
        throw IllegalCharacterException();

    this->name = n;
}

void Item::setPrice(double p) {
    this->price = p;
}

void Item::setDescription(string d) {

    if (d.find(";") != string::npos)
        throw IllegalCharacterException();

    this->description = d;
}

void Item::setStock(int s) {
    this->stock = s;
}

string Item::getName() {
    return this->name;
}

double Item::getPrice() {
    return this->price;
}

int Item::getStock() {
    return this->stock;
}

int Item::getId() {
    return this->id;
}
