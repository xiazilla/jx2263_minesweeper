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
	private:
		bool state;
		bool revealed;
		bool marked;
		int zoneValue;
	public: 
		zone() : state(false), revealed(false), marked(false), zoneValue(0) {}
		bool isBomb(){
			return state;
		}
		void setBomb(){
			state = true;
		}
		
	
};


class game {
	private: 
		vector<vector<zone> > board;
		int bombs_shown;
		int bombs_contained;
		int columns;
		int rows;
	public:
		game(int c, int r) : board(c, vector<zone>(r)), bombs_shown(0), bombs_contained(0), columns(c), rows(r) {}
		
		void addZone(int row, int column, zone z) {
			board[row][column] = z;
		}
		void createBombs(int num) {
			while(bombs_contained < num){	
				int x = rand() % columns;
				int y = rand() % rows;
				if(!(board[x][y].isBomb())){
					board[x][y].setBomb();
					++bombs_contained;
				}
			}
		}
};

#endif
