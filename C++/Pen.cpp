#include "Pen.h"

Pen::Pen(string n, double p, string d, int s, int i, string c, double t): Item(n, p, d, s, i), color(c), tipSize(t) {

    if (color.find(";") != string::npos)
        throw IllegalCharacterException();

}

string Pen::getDetails() {
    ostringstream detailsStream;
    detailsStream << fixed << setprecision(2) << ", Color: " << this->color << ", Tip: " << this->tipSize << " mm";

    return detailsStream.str();
}

string Pen::getCategory() {
    return "pen";
}

void Pen::setColor(string c) {

    if (c.find(";") != string::npos)
        throw IllegalCharacterException();

    this->color = c;

}

string Pen::getColor() {
    return this->color;
}

void Pen::setTipSize(double tSize) {
    this->tipSize = tSize;
}

double Pen::getTipSize() {
    return this->tipSize;
}
