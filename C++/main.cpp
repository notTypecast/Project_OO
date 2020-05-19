#include <iostream>
#include "Item.h"
#include "Pen.h"
#include "Owner.h"
#include <vector>

using namespace std;


void swapPointer(Owner * &opt);

int  main(){

	Owner * fo = new Owner("oldowner", "old@mail.com");

	cout << "This is owner mail now: " << fo->getMail() << endl;

	swapPointer(fo);

	cout << "This is owner mail after: " << fo->getMail() << endl;
	
	return 0;

	
}

void swapPointer(Owner * &opt){
	Owner * newopt = new Owner("newowner", "gio@gmail.com");
	opt = newopt;
	return;
}
