#include <iostream>
#include "Minsweeper.h"

using namespace std;

bool checkI(char i) {
	if(i == 'y' || i == 'Y') {
		return true;
	}
	return false;
}

int main() {
	cout << endl << endl << endl << endl << endl << endl;
	cout << "WELCOME TO JAMIE XIA'S MINESWEEPER." << endl;
	cout << "Would you like to play? (Y/N)" << endl;
	char i;
	cin  >> i;
	while(checkI(i)){
		zone* first = new zone();
		cout <<  "YES" << endl;
		i = 'n';
	}
	cout << "Thank you, come again." << endl;
	return 0;
}

