#pragma once

//#include "Cell.hpp"
#include <iostream>
#include <vector>
#include "Players.hpp"
//typedef std::pair<Cell, Cell> Move;


class Board{
	public:
		Cell cell[8][8];
		Players player1;
		Players player2;

		Board();
		void initBoard();

		bool isMoving;   //gives if the move was performed or not

		void setFirstPlayer(int x);
		bool selectCell(int x, int y);

		void Move(int newX, int newY);
		bool multipleMoveValid();
		void alterTurn();

        bool checkWin();
		bool checkStaleMate();


	private:
	    Players currentPlayer;
	    void setDisplacementvect(int x,int y);
	    bool isValidMove(int,int);
	    void update();
		int Xdisplacement,Ydisplacement;
		int xCoordSelectedCell;
		int yCoordSelectedCell;
};

