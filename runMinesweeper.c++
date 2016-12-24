//-----------------------------------------
// Copyright (C) 2016
// Jamie Xia
//-----------------------------------------

#include <iostream>
#include "Minsweeper.h"

using namespace std;

bool checkI(char i) {
	if(i == 'y' || i == 'Y') {
		return true;
	}
	return false;
}

bool checkMove(char c) {
	if(c == 'u' || c == 'U' || c == 'm' || c == 'M') {
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
		game game1(5, 10);

		int numBombs = 5;
		game1.createBombs(numBombs);
		cout << game1 << endl << endl;

		while(!(game1.endGame())) {
			
			cout << "u means uncover. m means mark. please enter your input in this format: 'u 2 3' where 2 is the column and 3 is the row." << endl;
			cout << "please enter your input now: " << endl;
			char move;
			int columns, rows;
			cin >> move;
			cin >> columns;
			cin >> rows;

			//cout << "move : " << move << " columns : " << columns << " rows : " << rows << endl << endl;

			if(checkMove(move)) {
				game1.makeMove(move, columns, rows);
			} else { 
				cout << endl <<  "Invalid input please try again" << endl << endl;
			}

		}
		
		i = 'n';
	}
	cout << "Thank you, come again." << endl;
	return 0;
}

