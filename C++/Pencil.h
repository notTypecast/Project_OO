#ifndef PENCIL_H
#define PENCIL_H

#include "Item.h"
#include <iomanip>

class Pencil: public Item {
    public:
        enum PENCIL_TYPE {
            H,
            B,
            HB
        };

        Pencil(string n, double p, string d, int s, int i, double t, PENCIL_TYPE p_t);

        string getDetails() override;

        string getCategory() override;

        void setTipSize(double size);

        double getTipSize();

        void setPencilType(PENCIL_TYPE type);

        PENCIL_TYPE getPencilType();

        string getPencilTypeString();


    private:
        double tipSize;
        PENCIL_TYPE pencilType;

        string enum_to_string[3];


};

#endif // PENCIL_H
