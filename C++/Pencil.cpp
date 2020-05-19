#include "Pencil.h"

Pencil::Pencil(string n, double p, string d, int s, int i, double t, PENCIL_TYPE p_t): Item(n, p, d, s i), tipSize(t), pencilType(p_t) {

}

string Pencil::getDetails() {
    return ", Type: " + this->enum_to_string[this->pencilType] + ", Tip Size: " + to_string(this->tipSize);
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
