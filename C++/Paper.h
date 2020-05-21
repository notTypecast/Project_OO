#ifndef PAPER_H
#define PAPER_H

#include "Item.h"

class Paper: public Item {
    private:
        int weight;
        int pages;

    public:
        Paper(string n, double p, string d, int s, int i, int w, int pg);

        string getDetails() override;

        string getCategory() override;

        void setWeight(int w);
        int getWeight();
        void setPages(int p);
        int getPages();

};

#endif // PAPER_H
