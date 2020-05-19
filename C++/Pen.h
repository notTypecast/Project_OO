#include "Item.h"
#include "IllegalCharacterException.h"
#ifndef PEN_H
#define PEN_H


class Pen: public Item {
    private:

        string color;
        double tipSize;

    public:

        Pen(string n, double p, string d, int s, int i, string c, double t);

        string getDetails();

        string getCategory();

        void setColor(string c);

        string getColor();

        void setTipSize(double s);

        double getTipSize();

};

#endif // PEN_H
