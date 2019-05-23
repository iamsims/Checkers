#pragma once

#include "Cell.hpp"
#include <iostream>
#include "Player.hpp"
#include <vector>

struct _Board
    {
    int _cell[8][8];
    int _currentPlayer;
    int _mode;

    } ;

struct Coords {
    int x1 : 4;
    int y1 : 4;
    int x2 : 4;
    int y2 : 4;
    Coords ( int x1_, int y1_, int x2_, int y2_ );
    bool operator!= ( const Coords &B );
};

struct Move {
    std::vector< Coords > coords;
    Move(){}
    Move( int x1, int y1, int x2, int y2 );
    Move( Coords c );
    void add( Coords c );
    bool operator== ( const Move &B );
};

using namespace std;

class Board{
	public:
		Cell cell[8][8];
		Player player1;
		Player player2;
		Board();
		void initBoard();
		bool isMoving;
		bool _isMoving;
		void setFirstPlayer(int x);
		bool selectCell(int x, int y);
		bool multipleMoveValid();
		void alterTurn();
    int checkWin();
		bool checkStaleMate();
		bool mover(int newX, int newY);
		Player currentPlayer;
		int xinmultiple;
		int yinmultiple;
		int xCoordSelectedCell;
		int yCoordSelectedCell;
		bool validmultiplecheck;
		friend std::ostream& operator<<(std::ostream& out, const Board &board);
		bool updatevar;
		int drawCounter, redP, blackP, redK, blackK;
	    bool checkCapture( int x, int y );
	    bool checkCapture( bool color );
	    std::vector< Move > getMoveSequences( Move move, Board b );
	    std::vector< Move > getViableMoves( bool color );
	    std::vector< Move > getViableMoves( int x, int y );
	    void capture( int x1, int y1, int x2, int y2 );
	    int move( Coords m );
	    int move( Move m );
	    int move( int x1, int y1, int x2, int y2, bool color );
	    int checkState( bool color );
	    int evaluateField( int x, int y );
	    int evaluateBoard( bool color, bool side );
	    int mode ;
	    int load();
	    void save();

	private:

    struct _Board _board;
	  void setDisplacementvect(int x,int y);
	  bool isValidMove(int,int);
	  void update();
		int Xdisplacement,Ydisplacement;
		bool checkcaptureavailable();
};

_Board loadfromfile ();
void savetofile(_Board _fboard);
