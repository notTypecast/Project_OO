#ifndef PEN_H
#define PEN_H

#include "Item.h"
#include "IllegalCharacterException.h"

class Pen: public Item {
    private:

        string color;
        double tipSize;

    public:

        Pen(string n, double p, string d, int s, int i, string c, double t);

        string getDetails() override;

        string getCategory() override;

        void setColor(string c);

        string getColor();

        void setTipSize(double s);

        double getTipSize();

};

#endif // PEN_H
