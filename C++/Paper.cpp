#include "Paper.h"

Paper::Paper(string n, double p, string d, int s, int i, int w, int pg): Item(n, p, d, s, i), weight(w), pages(pg) {

}

string Paper::getDetails() {
    return ", Paper weight " + to_string(this->weight) + "g " + ", Pages of paper : " + to_string(this->pages);
}

string Paper::getCategory() {
    return "paper";
}

void Paper::setWeight(int w) {
    this->weight = w;
}

int Paper::getWeight() {
    return this->weight;
}

void Paper::setPages(int p) {
    this->pages = p;
}

int Paper::getPages() {
    return this->pages;
}
