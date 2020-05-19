#include "Item.h"
#ifndef PAPER_H
#define PAPER_H


class Paper: public Item {
    private:
        int weight;
        int pages;

    public:
        Paper(string n, double p, string d, int s, int i, int sec);

        string getDetails();
        void setWeight(int w);
        int getWeight();
        void setPages(int p);
        int getPages();

};

#endif // PAPER_H
