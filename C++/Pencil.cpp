#include "Pencil.h"

Pencil::Pencil(string n, double p, string d, int s, int i, double t, PENCIL_TYPE p_t): Item(n, p, d, s, i), tipSize(t), pencilType(p_t) {

    this->enum_to_string[0] = "H";
    this->enum_to_string[1] = "B";
    this->enum_to_string[2] = "HB";

}

string Pencil::getDetails() {

    ostringstream detailsStream;
    detailsStream << fixed << setprecision(2) << ", Type: " << this->enum_to_string[this->pencilType] << ", Tip Size: " << this->tipSize << "mm";

    return detailsStream.str();
        
}

string Pencil::getCategory() {
    return "pencil";
}

void Pencil::setTipSize(double s) {
    this->tipSize = s;
}

double Pencil::getTipSize() {
    return this->tipSize;
}

void Pencil::setPencilType(PENCIL_TYPE type) {
    this->pencilType = type;
}

Pencil::PENCIL_TYPE Pencil::getPencilType() {
    return this->pencilType;
}

string Pencil::getPencilTypeString() {

    return this->enum_to_string[this->pencilType];

}
