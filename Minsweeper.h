//-----------------------------
// Copyright (C) 2016
// Jamie Xia
//-----------------------------

#ifndef Minesweeper_h
#define Minesweeper_h

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class zone {
	friend ostream &operator<<(ostream &lhs, const zone &rhs) {
		if(!(rhs.revealed)) {
			lhs << "?";
		} else if(rhs.marked) {
			lhs << "b";
		} else if(!(rhs.state)){
			lhs << rhs.zoneValue;
		} else {
			lhs << "!";
		}
		return lhs;
	}
	private:
		bool state;
		bool revealed;
		bool marked;
		int zoneValue;
	public: 
		zone() : state(false), revealed(false), marked(false), zoneValue(0) {}
		zone(bool bomb) : state(bomb), revealed(false), marked(false), zoneValue(0) {}

		bool isBomb(){
			return this->state;
		}
		void setBomb(){
			this->state = true;
		}

		void increaseZoneValue() {
			++(this->zoneValue);
		}
		bool isRevealed() {
			return this->revealed;
		}	
		bool isMarked() {
			return this->marked;
		}	
		bool zero() {
 			return this->zoneValue == 0;	
		}
		bool uncover() { // returns true if valid move, false if bomb
			this->revealed = true;
			if(this->state) {
				return false;
			}
			return true;
		}
};


class game {
	friend ostream &operator<<(ostream &lhs, const game &rhs) {
		lhs << "   ";
		for(int i = 0; i < rhs.columns; ++i) {
			lhs << i << " ";
		}
		lhs << endl << endl;;
		for(int x = 0; x < rhs.rows; ++x) {
			lhs << x << "  ";
				
			for(int y = 0; y < rhs.columns; ++y) {
				lhs << rhs.board[y][x] << " ";
			}
			lhs << endl;
		}
		return lhs;
	}
	private: 
		vector<vector<zone> > board;
		int bombs_shown;
		int bombs_contained;
		int columns;
		int rows;
		bool bombHit;
		int numBombs;
	public:
		game(int c, int r) : board(c, vector<zone>(r)), bombs_shown(0), bombs_contained(0), columns(c), rows(r), bombHit(false), numBombs(0) {}
		
		void addZone(int row, int column, zone z) {
			board[row][column] = z;
		}
		
		void increaseNeighbors(int i, int j) {
			if(i-1 >= 0) { //left
				board[i-1][j].increaseZoneValue();
				if(j-1 >= 0) { //top left
					board[i-1][j-1].increaseZoneValue();
				}
				if(j+1 < rows) { //bottom left
					board[i-1][j+1].increaseZoneValue();
				}
			}
			if(i+1 < columns) { //right
				board[i+1][j].increaseZoneValue(); 
				if(j-1 >= 0) { //bottom left
					board[i+1][j-1].increaseZoneValue();
				}
				if(j+1 < rows) { //bottom right
					board[i+1][j+1].increaseZoneValue();
				}
			}
			if(j-1 >= 0) {
				board[i][j-1].increaseZoneValue();
			}
			if(j+1 < rows) {
				board[i][j+1].increaseZoneValue();
			}
		}

		bool allShownRevealed(){
			for(int i = 0; i < columns; ++i) {
				for(int j = 0; j < rows; ++j) {
					if(!(board[i][j].isRevealed()) || !(board[i][j].isMarked())) {
						return false;
					}
					if(board[i][j].isMarked() && !(board[i][j].isBomb())) {
						return false;
					}
				}
			}
			return true;

		}

		bool endGame() {
			if(bombHit) { 
				cout << "GAME OVER U SUCK HA HA HA" << endl;
				return true;
			}
			if(bombs_shown == numBombs && allShownRevealed()) {
				cout << "U WIN GOOD JOB" << endl;
				return true;
			}
			return false;
		}

		void createBombs(int num) {
			srand(time(NULL));

			numBombs = num;

//			increaseNeighbors(3, 3);

			while(bombs_contained < num){	
				int x = rand() % columns;
				int y = rand() % rows;
				if(!(board[x][y].isBomb())){
					zone temp = new zone(true);
					board[x][y] = temp;
					++bombs_contained;
					increaseNeighbors(x, y);
				}
			}
		}
		int getColumns() {
			return columns;
		}
		int getRows() {
			return rows;
		}

		void setZoneValues() {
			for(int i = 0; i < columns; ++i) {
				for(int j = 0; j < rows; ++j) {
					if(board[i][j].isBomb()){
						increaseNeighbors(i, j);
					}
				}
			}
		}

		void revealZeroes(int c, int r) {
/*			if(board[c][r].zero()) {
				if(r-1 >= 0) {
					uncover(c, r-1);
					if(c+1 < columns) {
						uncover(c+1, r-1);
					}
					if(c-1 >= 0) {
						uncover(c-1, r-1);			
					}
				}
				if(r+1 < rows) {
					uncover(c, r+1);
					if(c+1 < columns) {
						uncover(c+1, r+1);
					}
					if(c-1 >= 0) {
						uncover(c-1, r+1);
					}
				}				
				if(c+1 < columns) {
					uncover(c+1, r);
				}	
				if(c-1 < columns) {
					uncover(c-1, r);
				}
			}*/
		}

		void uncover(int c, int r) {
			if(!(board[c][r].uncover())) {
				cout << "YOU HIT A BOMB!" << endl;
				bombHit = true;
				cout << *this << endl << endl ;	
			}
			revealZeroes(c, r);
		}

		void makeMove(char ch, int c, int r) {
			if(c >= 0 && c < columns && r >= 0 && r < rows) {
				switch(ch){
					case 'u' :
						cout << endl <<"IN HERE1" << endl << endl;
						uncover(c, r);
						cout << endl <<"IN HEREi1" << endl << endl;
						break;
					case 'U' :
						uncover(c, r);
						break;
					case 'm' :
						break;
					case 'M' : 
						break;
				}
				cout << *this << endl << endl;
			} else { 
				cout << endl << "NOT WITHIN THE BOUNDS OF THE BOARD. TRY AGAIN" << endl;
			}
		}

};

#endif
