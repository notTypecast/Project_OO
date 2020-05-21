#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



int  main(){

	string hello = "worlDFd";
	transform(hello.begin(), hello.end(), hello.begin(), ::tolower);
	cout << hello << endl;
	
}

