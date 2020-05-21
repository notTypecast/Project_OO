#include "Notebook.h"

Notebook::Notebook(string n, double p, string d, int s, int i, int sec): Item(n, p, d, s, i), sections(sec) {

}

string Notebook::getDetails() {
    return ", Sections: " + to_string(this->sections);
}

string Notebook::getCategory() {
    return "notebook";
}

void Notebook::setSections(int s) {
    this->sections = s;
}

int Notebook::getSections() {
    return this->sections;
}
