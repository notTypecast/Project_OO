#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include "Item.h"

class Notebook: public Item {
    private:
        int sections;

    public:
        Notebook(string n, double p, string d, int s, int i, int sec);

        string getDetails() override;

        string getCategory() override;

        void setSections(int s);
        int getSections();


};

#endif // NOTEBOOK_H
