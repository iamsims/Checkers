#include "Board.hpp"
#include "Player.hpp"

using namespace std;

Coords::Coords ( int x1_, int y1_, int x2_, int y2_ ) {
    x1 = x1_;
    y1 = y1_;
    x2 = x2_;
    y2 = y2_;
}
bool Coords::operator!= ( const Coords &B ) {
    if ( this -> x1 != B.x1 ||
            this -> y1 != B.y1 ||
            this -> x2 != B.x2 ||
            this -> y2 != B.y2 )
        return true;
    return false;
}

// Moves
Move::Move( int x1, int y1, int x2, int y2 ) {
    coords.emplace_back( x1, y1, x2, y2 );
}

Move::Move( Coords c ) {
    coords.push_back( c );
}
void Move::add( Coords c ) {
    coords.insert( coords.begin(), c );
}
bool Move::operator== ( const Move &B ) {
    if ( this -> coords.size() != B.coords.size() )
        return false;
    else
        for ( unsigned int i = 0; i < coords.size(); i++ )
            if ( this -> coords[i] != B.coords[i] )
                return false;
    return true;
}

Board::Board(){
        // Simax, what had to be done, it's done
        // modify code

    player1(Player::YELLOW);
    player2(Player::WHITE);
    initBoard();
};

int Board::load ()
{
std::cout<<"loading "<<std::endl;
// ifstream input_file("data.dat", ios::binary);
//    input_file.read((char*)&_board, sizeof(_board));
//    input_file.close();
// _board = loadfromfile( );
for ( int i = 0; i < 8; i++ ){
        for ( int j = 0; j < 8; j++ )
            std::cout<<_board._cell[i][j]<<' ' ;
            std::cout<<std::endl;
                              }

 std::cout<<_board._currentPlayer;
 std::cout<<_board._mode;
 std::cout <<"it was in load just after fetching from file"<<std::endl;
     std::cout<<"loading"<<std::endl;
     for ( int i = 0; i < 8; i++ )
        for ( int j = 0; j < 8; j++ )
            cell[i][j].setTYPE((TYPE)_board._cell[i][j]);
  if (_board._currentPlayer==(int)player1.getcolour())
        currentPlayer=player1;

    else currentPlayer=player2;

//for debugging
    for ( int i = 0; i < 8; i++ ){
        for ( int j = 0; j < 8; j++ )
            std::cout<<cell[i][j].getTYPE()<<' ' ;
            std::cout<<std::endl;
                              }
 std::cout<<currentPlayer.getcolour();
 std::cout<<mode;
    return _board._mode;   //board mode is set out in the gamestate externally so no need to assign to mode
}


void Board::save()
{

std::cout<<"i am save function"<<std::endl;
std::cout<<"saving"<<std::endl;
//    ofstream output_file("game.dat", ios::binary);
 for ( int i = 0; i < 8; i++ )
        for ( int j = 0; j < 8; j++ )
            _board._cell[i][j]=(int)cell[i][j].getTYPE();
 _board._currentPlayer=(int)currentPlayer.getcolour();
 _board._mode=mode;

//  savetofile(_board);

 //for debugging

for ( int i = 0; i < 8; i++ ){
        for ( int j = 0; j < 8; j++ )
            std::cout<<_board._cell[i][j]<<' ' ;
            std::cout<<std::endl;
                              }

 std::cout<<_board._currentPlayer;
 std::cout<<_board._mode;

// ofstream output_file("data.dat", ios::binary);
// output_file.write((char*)&_board, sizeof(_board));
// output_file.close();

}


void Board::initBoard(){
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            if ( i%2 != j%2 ) {
                if ( i < 3 )
                    cell[i][j].setTYPE( WHITE_PAWN);
                else if ( i > 4 )
                    cell[i][j].setTYPE(YELLOW_PAWN);
            }
        }
    }
		// cell[0][7].setTYPE(WHITE_PAWN);
		// cell[1][6].setTYPE(YELLOW_PAWN);
		// cell[7][0].setTYPE(WHITE_PAWN);
		// // cell[6][1].setTYPE(YELLOW_PAWN);
}

std::ostream& operator<<(std::ostream& out, const Board &board){
    for(int i=0; i< 8; i++){
        for( int j=0; j<8; j++ ){
            const char* s = 0;
            #define PROCESS_VAL(p) case(p): s = #p; break;
            switch(board.cell[i][j].getTYPE()){
                    PROCESS_VAL(EMPTY);
                    PROCESS_VAL(WHITE_PAWN);
                    PROCESS_VAL(WHITE_KING);
                    PROCESS_VAL(YELLOW_PAWN);
                    PROCESS_VAL(YELLOW_KING);
            }
            #undef PROCESS_VAL
            out << s << ",    ";
        }
        out << std::endl << std::endl;
    }
    out << "========== Board State ==================" << std::endl;
  return out;
}

void Board::setFirstPlayer(int col)
{
    if (col==player1.getcolour())
        currentPlayer=player1;
    else currentPlayer=player2;
}

bool Board::selectCell(int x, int y)
{
    if (cell[x][y].getTYPE()==currentPlayer.getkey(0) || cell[x][y].getTYPE() ==currentPlayer.getkey(1) )
    {
        xCoordSelectedCell=x;
        yCoordSelectedCell=y;
                // std::cout << "yes your turn"<< std::endl;
                // _isMoving = true;
        return 1;
    }
    else {
                // std::cout << "not your turn"<< std::endl;
        // _isMoving = false;
        return 0;
    }
}

void Board::alterTurn()
{
    if (currentPlayer.getcolour()==player1.getcolour())
        currentPlayer=player2;

    else currentPlayer=player1;

}



void Board::setDisplacementvect(int newX,int newY)
{
    Xdisplacement=newX-xCoordSelectedCell;
    Ydisplacement= newY-yCoordSelectedCell;
}


bool Board::isValidMove(int newX, int newY)
{
    setDisplacementvect(newX,newY);
    int valid=0; //in general case because in king mode it can go anywhere no matter what
    if ((xCoordSelectedCell+Xdisplacement)<0||(xCoordSelectedCell+Xdisplacement)>7||(yCoordSelectedCell+Ydisplacement)<0||(yCoordSelectedCell+Ydisplacement) >7)
        return valid;
    int newstate =cell[xCoordSelectedCell+Xdisplacement][yCoordSelectedCell+Ydisplacement].getTYPE();
    int oldstate=cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE();

    if (checkcaptureavailable()&&abs(Xdisplacement)!=2)
        return false;
    if ((newstate==EMPTY) && ((abs(Xdisplacement)==1 && abs(Ydisplacement)==1)||(abs(Xdisplacement)==2 && abs(Ydisplacement)==2)))
    {
    if (oldstate==WHITE_PAWN && Xdisplacement>0)
        {
            valid=1;
            if (Xdisplacement==2)                                  //y maybe negative or positive
             if (!(cell[xCoordSelectedCell+1][yCoordSelectedCell+Ydisplacement/2].getTYPE()==YELLOW_KING ||
                cell[xCoordSelectedCell+Xdisplacement/2][yCoordSelectedCell+Ydisplacement/2].getTYPE()==YELLOW_PAWN))
                valid=0;

        }

    if (oldstate == YELLOW_PAWN && Xdisplacement<0)
        {

        valid=1;
        if (Xdisplacement==-2)
             if (!(cell[xCoordSelectedCell-1][yCoordSelectedCell+Ydisplacement/2].getTYPE()==WHITE_KING ||
                cell[xCoordSelectedCell-1][yCoordSelectedCell+Ydisplacement/2].getTYPE()==WHITE_PAWN))
                valid=0;


        }

    if  (oldstate== WHITE_KING || oldstate== YELLOW_KING)
      {
             valid=1;
            if (abs (Ydisplacement)==2 && oldstate==WHITE_KING)
             {if (!(cell[xCoordSelectedCell+Xdisplacement/2][yCoordSelectedCell+Ydisplacement/2].getTYPE()==YELLOW_KING ||
                cell[xCoordSelectedCell+Xdisplacement/2][yCoordSelectedCell+Ydisplacement/2].getTYPE()==YELLOW_PAWN))
                valid=0;
             }

            else if (abs (Ydisplacement)==2 && oldstate==YELLOW_KING)
             {if (!(cell[xCoordSelectedCell+Xdisplacement/2][yCoordSelectedCell+Ydisplacement/2].getTYPE()==WHITE_KING ||
                cell[xCoordSelectedCell+Xdisplacement/2][yCoordSelectedCell+Ydisplacement/2].getTYPE()==WHITE_PAWN))
                valid=0;
             }

    }
    }
    if(validmultiplecheck)
    {
        if (xinmultiple!=xCoordSelectedCell||yinmultiple!=yCoordSelectedCell)
        {
            valid=0;
        }
    }
      return valid;

}


bool Board::mover(int newX, int newY)
{     //no multiple moves here ...called after checking if valid moves or not
    if (isValidMove(newX,newY))
    {

    cell[newX][newY].setTYPE(cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE());
    cell[xCoordSelectedCell][yCoordSelectedCell].setTYPE(EMPTY);


    if (abs(Xdisplacement)==2)  //x and y remain the same when the displacement is any move step move valid position
    {
         cell[xCoordSelectedCell+Xdisplacement/2][yCoordSelectedCell+Ydisplacement/2].setTYPE(EMPTY);

    }

   selectCell(newX,newY);
   update();
   isMoving=1;
     return 1;
    }
        else {
            isMoving=0;return 0;
        }

}



void Board::update( )
{
    updatevar=0;
 if (cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()== WHITE_PAWN && xCoordSelectedCell==7)
   {cell[xCoordSelectedCell][yCoordSelectedCell].setTYPE(WHITE_KING);
   updatevar=1;
   }
   

 if (cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()== YELLOW_PAWN && xCoordSelectedCell==0)
    {cell[xCoordSelectedCell][yCoordSelectedCell].setTYPE(YELLOW_KING);
    updatevar=1;
    }
    
    
}


bool Board::multipleMoveValid()
{
    if (abs(Xdisplacement)==2)
    {
        if (cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()==WHITE_KING)
        {
            if ((cell[xCoordSelectedCell+1][yCoordSelectedCell-1].getTYPE()==YELLOW_KING && cell[xCoordSelectedCell+2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0 &&(xCoordSelectedCell+2)<=7) 
            || (cell[xCoordSelectedCell+1][yCoordSelectedCell-1].getTYPE()==YELLOW_PAWN && cell[xCoordSelectedCell+2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0 &&(xCoordSelectedCell+2)<=7)||
                (cell[xCoordSelectedCell+1][yCoordSelectedCell+1].getTYPE()==YELLOW_KING &&cell[xCoordSelectedCell+2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7 &&(xCoordSelectedCell+2)<=7)|| 
                (cell[xCoordSelectedCell+1][yCoordSelectedCell+1].getTYPE()==YELLOW_PAWN &&cell[xCoordSelectedCell+2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7 &&(xCoordSelectedCell+2)<=7)||
                (cell[xCoordSelectedCell-1][yCoordSelectedCell-1].getTYPE()==YELLOW_KING &&cell[xCoordSelectedCell-2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0 &&(xCoordSelectedCell-2)>=0)|| 
                (cell[xCoordSelectedCell-1][yCoordSelectedCell-1].getTYPE()==YELLOW_PAWN &&cell[xCoordSelectedCell-2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0 &&(xCoordSelectedCell-2)>=0)||
                (cell[xCoordSelectedCell-1][yCoordSelectedCell+1].getTYPE()==YELLOW_KING &&cell[xCoordSelectedCell-2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7 &&(xCoordSelectedCell-2)>=0)|| 
                (cell[xCoordSelectedCell-1][yCoordSelectedCell+1].getTYPE()==YELLOW_PAWN &&cell[xCoordSelectedCell-2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7 &&(xCoordSelectedCell-2)>=0))
                return true;
        }

        if (cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()==WHITE_PAWN )
        {
            if (xCoordSelectedCell==6 ||xCoordSelectedCell==7)
            {
                return false;
            }
            else
            {
            if ((cell[xCoordSelectedCell+1][yCoordSelectedCell-1].getTYPE()==YELLOW_KING &&cell[xCoordSelectedCell+2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0)
            || (cell[xCoordSelectedCell+1][yCoordSelectedCell-1].getTYPE()==YELLOW_PAWN&&cell[xCoordSelectedCell+2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0)
            ||(cell[xCoordSelectedCell+1][yCoordSelectedCell+1].getTYPE()==YELLOW_KING &&cell[xCoordSelectedCell+2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7)
            || (cell[xCoordSelectedCell+1][yCoordSelectedCell+1].getTYPE()==YELLOW_PAWN &&cell[xCoordSelectedCell+2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7))
                return true;
            }
        }

        if (cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()==YELLOW_KING)
        {
            if ((cell[xCoordSelectedCell+1][yCoordSelectedCell-1].getTYPE()==WHITE_KING &&cell[xCoordSelectedCell+2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0 &&(xCoordSelectedCell+2)<=7)
            || (cell[xCoordSelectedCell+1][yCoordSelectedCell-1].getTYPE()==WHITE_PAWN&&cell[xCoordSelectedCell+2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0 &&(xCoordSelectedCell+2)<=7)
            || (cell[xCoordSelectedCell+1][yCoordSelectedCell+1].getTYPE()==WHITE_KING &&cell[xCoordSelectedCell+2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7 &&(xCoordSelectedCell+2)<=7)
                || (cell[xCoordSelectedCell+1][yCoordSelectedCell+1].getTYPE()==WHITE_PAWN &&  cell[xCoordSelectedCell+2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7 &&(xCoordSelectedCell+2)<=7)
                ||(cell[xCoordSelectedCell-1][yCoordSelectedCell-1].getTYPE()==WHITE_KING && cell[xCoordSelectedCell-2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0 &&(xCoordSelectedCell-2)>=0)
                 || (cell[xCoordSelectedCell-1][yCoordSelectedCell-1].getTYPE()==WHITE_PAWN &&  cell[xCoordSelectedCell-2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0 &&(xCoordSelectedCell-2)>=0)
                 ||(cell[xCoordSelectedCell-1][yCoordSelectedCell+1].getTYPE()==WHITE_KING &&  cell[xCoordSelectedCell-2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7 &&(xCoordSelectedCell-2)>=0) 
                || (cell[xCoordSelectedCell-1][yCoordSelectedCell+1].getTYPE()==WHITE_PAWN &&  cell[xCoordSelectedCell-2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7 &&(xCoordSelectedCell-2)>=0))
                return true;
        }
        if (cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()==YELLOW_PAWN)
        {
            if (xCoordSelectedCell==0 ||xCoordSelectedCell==1)
            {
                return false;
            }
            else 
            {
            if    ((cell[xCoordSelectedCell-1][yCoordSelectedCell-1].getTYPE()==WHITE_KING &&  cell[xCoordSelectedCell-2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0)
            || (cell[xCoordSelectedCell-1][yCoordSelectedCell-1].getTYPE()==WHITE_PAWN &&  cell[xCoordSelectedCell-2][yCoordSelectedCell-2].getTYPE()==EMPTY &&(yCoordSelectedCell-2)>=0)
            ||(cell[xCoordSelectedCell-1][yCoordSelectedCell+1].getTYPE()==WHITE_KING && cell[xCoordSelectedCell-2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7)
                || (cell[xCoordSelectedCell-1][yCoordSelectedCell+1].getTYPE()==WHITE_PAWN && cell[xCoordSelectedCell-2][yCoordSelectedCell+2].getTYPE()==EMPTY &&(yCoordSelectedCell+2)<=7) )
                return true;
            }
        }
    }

    return false;
}
bool Board::checkcaptureavailable()
{

    for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if ((cell[i][j].getTYPE()==WHITE_PAWN || cell[i][j].getTYPE()==WHITE_KING)&&(currentPlayer.getcolour() ==Player::Colour::WHITE))
                {
                    if (((cell[i+1][j-1].getTYPE()==YELLOW_PAWN||cell[i+1][j-1].getTYPE()==YELLOW_KING)&& cell[i+2][j-2].getTYPE()==EMPTY && (i+2)<=7&& (j-2)>=0)

                    ||((cell[i+1][j+1].getTYPE()==YELLOW_PAWN||cell[i+1][j+1].getTYPE()==YELLOW_KING)&& cell[i+2][j+2].getTYPE()==EMPTY && (i+2)<=7&& (j+2)<=7))
                    return true;
                } 
                if ((cell[i][j].getTYPE()== WHITE_KING)&&(currentPlayer.getcolour() ==Player::Colour::WHITE))
                {
                   if (((cell[i-1][j-1].getTYPE()==YELLOW_PAWN||cell[i-1][j-1].getTYPE()==YELLOW_KING)&& cell[i-2][j-2].getTYPE()==EMPTY && (i-2)>=0&& (j-2)>=0)

                    ||((cell[i-1][j+1].getTYPE()==YELLOW_PAWN||cell[i-1][j+1].getTYPE()==YELLOW_KING)&& cell[i-2][j+2].getTYPE()==EMPTY && (i-2)>=0&& (j+2)<=7))
                    return true; 
                }

                if ((cell[i][j].getTYPE()==YELLOW_PAWN || cell[i][j].getTYPE()==YELLOW_KING)&&(currentPlayer.getcolour() ==Player::Colour::YELLOW))
                {
                    if (((cell[i-1][j-1].getTYPE()==WHITE_PAWN||cell[i-1][j-1].getTYPE()==WHITE_KING)&& cell[i-2][j-2].getTYPE()==EMPTY && (i-2)>=0&& (j-2)>=0)

                    ||((cell[i-1][j+1].getTYPE()==WHITE_PAWN||cell[i-1][j+1].getTYPE()==WHITE_KING)&& cell[i-2][j+2].getTYPE()==EMPTY && (i-2)>=0&& (j+2)<=7))
                    return true;
                } 
                if ((cell[i][j].getTYPE()== YELLOW_KING)&&(currentPlayer.getcolour() ==Player::Colour::YELLOW))
                {
                   if (((cell[i+1][j-1].getTYPE()==WHITE_PAWN||cell[i+1][j-1].getTYPE()==WHITE_KING)&& cell[i+2][j-2].getTYPE()==EMPTY && (i+2)<=7&& (j-2)>=0)

                    ||((cell[i+1][j+1].getTYPE()==WHITE_PAWN||cell[i+1][j+1].getTYPE()==WHITE_KING)&& cell[i+2][j+2].getTYPE()==EMPTY && (i+2)<=7&& (j+2)<=7))
                    return true; 
                }
            
            }

}
return false;
}





bool Board::checkStaleMate()   // return 0 if not stalemate and 1 if stalemate
{
    bool color = (currentPlayer.getcolour() == Player::WHITE)?0:1;
		std::vector <Move> move = getViableMoves(color);
		if(move.empty()){
			return true;	
		}
		return false;
}


int Board::checkWin()
{
	if(checkStaleMate()){
		// alterTurn();
		return 1;
	}

     int nOpponents=0;

    for (int i =0;i<8;i++)
    {
        for (int j =0;j<8;j++)
        {
            if (currentPlayer.getcolour() ==Player::Colour::WHITE)
            if (cell[i][j].getTYPE()==WHITE_PAWN || cell[i][j].getTYPE()==WHITE_KING)
                nOpponents++;
 

            if (currentPlayer.getcolour()==Player::Colour::YELLOW)
            if (cell[i][j].getTYPE()==YELLOW_PAWN || cell[i][j].getTYPE()==YELLOW_KING)
                nOpponents++;
        }
    }

    if (nOpponents==0) return 1;
    else return 0;

}




bool Board::checkCapture( int x, int y ) {
    // red 0, black 1
    bool color = ( cell[x][y].getTYPE() == WHITE_PAWN || cell[x][y].getTYPE() == WHITE_KING ) ? 0 : 1;
    // check for pawns
    if ( cell[x][y].getTYPE() == WHITE_PAWN || cell[x][y].getTYPE() == YELLOW_PAWN ) {
        for ( int a : {-1, 1} ) {
            for ( int b : {-1, 1} ) {

							if( color ){
									if( (a==1 && b ==1 ) || (a==1 && b ==-1 )){
										break;
									}
								}else{
									if( (a==-1 && b ==-1 ) || (a==-1 && b ==1 )){
										break;
									}
								}

                int i = x + a;
                int j = y + b;
                if ( i+a < 8 && i+a >= 0 && j+b < 8 && j+b >= 0 ) {
                    if ( color ) {
                        if ( cell[i][j].getTYPE() == WHITE_KING || cell[i][j].getTYPE() == WHITE_PAWN )
                            if ( cell[i+a][j+b].getTYPE() == EMPTY )
                                return true;
                    } else {
                        if ( cell[i][j].getTYPE() == YELLOW_KING || cell[i][j].getTYPE() == YELLOW_PAWN )
                            if ( cell[i+a][j+b].getTYPE() == EMPTY )
                                return true;
                    }
                }
            }
        }
    }
    // check for kings
    else if ( cell[x][y].getTYPE() == WHITE_KING || cell[x][y].getTYPE() == YELLOW_KING ) {
        for ( int a : {-1, 1} ) {
            for ( int b : {-1, 1} ) {
                int i = x + a;
                int j = y + b;
                if ( i+a < 8 && i+a >= 0 && j+b < 8 && j+b >= 0 ) {
                    if ( color ) {
                        if ( cell[i][j].getTYPE() == YELLOW_KING || cell[i][j].getTYPE() == YELLOW_PAWN )
                            break;
                        if ( cell[i][j].getTYPE() == WHITE_KING || cell[i][j].getTYPE() == WHITE_PAWN ) {
                            if ( cell[i+a][j+b].getTYPE() == EMPTY )
                                return true;
                            else
                                break;
                        }
                    } else {
                        if ( cell[i][j].getTYPE() == WHITE_KING || cell[i][j].getTYPE() == WHITE_PAWN )
                            break;
                        if ( cell[i][j].getTYPE() == YELLOW_KING || cell[i][j].getTYPE() == YELLOW_PAWN ) {
                            if ( cell[i+a][j+b].getTYPE() == EMPTY )
                                return true;
                            else
                                break;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Board::checkCapture( bool color ) {
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            if ( color ) {
                if ( cell[i][j].getTYPE() == YELLOW_KING || cell[i][j].getTYPE() == YELLOW_PAWN )
                    if ( checkCapture( i, j ) )
                        return true;
            } else {
                if ( cell[i][j].getTYPE() == WHITE_KING || cell[i][j].getTYPE() == WHITE_PAWN )
                    if ( checkCapture( i, j ) )
                        return true;
            }
        }
    }
    return false;
}

// get all viable sequences after first move
std::vector< Move > Board::getMoveSequences( Move move, Board b ) {
    std::vector< Move > moves;
    if ( b.move( move.coords[0] ) == 1 ) {
        moves.emplace_back( move.coords[0] );
    } else {
        for ( auto& m : b.getViableMoves( move.coords[0].x2, move.coords[0].y2 ) ) {
            std::vector< Move > tmp = getMoveSequences( m, b );
            moves.insert( moves.end(), tmp.begin(), tmp.end() );
        }
        for ( auto& m : moves ) {
            m.add( move.coords[0] );
        }
    }
    return moves;
}
//
// // get all viable first moves for a color
std::vector< Move > Board::getViableMoves( bool color ) {
    std::vector< Move > moves;
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            if ( color ) {
                if ( cell[i][j].getTYPE() == YELLOW_KING || cell[i][j].getTYPE() == YELLOW_PAWN ) {
                    auto tmp = getViableMoves( i, j );
                    for ( auto& m : tmp ) {
                        auto tmp2 = getMoveSequences( m, *this );
                        moves.insert( moves.end(), tmp2.begin(), tmp2.end() );
                    }
                }
            } else {
                if ( cell[i][j].getTYPE() == WHITE_KING || cell[i][j].getTYPE() == WHITE_PAWN ) {
                    auto tmp = getViableMoves( i, j );
                    for ( auto& m : tmp ) {
                        auto tmp2 = getMoveSequences( m, *this );
                        moves.insert( moves.end(), tmp2.begin(), tmp2.end() );
                    }
                }
            }
        }
    }
    return moves;
}
//
// // get all viable first moves for a pawn
std::vector< Move > Board::getViableMoves( int x, int y ) {
    bool color;
    std::vector< Move > moves;
    // if a field is empty return empty vector
    if ( cell[x][y].getTYPE() == EMPTY )
        return moves;
    if ( cell[x][y].getTYPE() == WHITE_PAWN || cell[x][y].getTYPE() == WHITE_KING ) {
        color = 0;
    } else {
        color = 1;
    }
    // If a capture is possible on the other move just return empty vector
    if ( checkCapture( color ) != checkCapture( x, y ) )
        return moves;
    // Check for pawns
    if ( cell[x][y].getTYPE() == WHITE_PAWN || cell[x][y].getTYPE() == YELLOW_PAWN ) {
        // If there are no capturing opportunities
        if ( !checkCapture( x, y ) ) {
            int xdir = color ? -1 : 1;
            if ( y < 7 )
                if ( cell[x+xdir][y+1].getTYPE() == EMPTY )
                    moves.push_back( Move( x, y, x+xdir, y+1 ) );
            if ( y > 0 )
                if ( cell[x+xdir][y-1].getTYPE() == EMPTY )
                    moves.push_back( Move( x, y, x+xdir, y-1 ) );
        // If there are captures available
        } else {
            for ( int a : {-1, 1} ) {
                for ( int b : {-1, 1} ) {
                    int i = x + a;
                    int j = y + b;
                    if ( i+a < 8 && i+a >= 0 && j+b < 8 && j+b >= 0 ) {
                        if ( color ) {
                            if ( cell[i][j].getTYPE() == WHITE_KING || cell[i][j].getTYPE() == WHITE_PAWN )
                                if ( cell[i+a][j+b].getTYPE() == EMPTY )
                                    moves.push_back( Move( x, y, i+a, j+b ) );
                        } else {
                            if ( cell[i][j].getTYPE() == YELLOW_KING || cell[i][j].getTYPE() == YELLOW_PAWN )
                                if ( cell[i+a][j+b].getTYPE() == EMPTY )
                                    moves.push_back( Move( x, y, i+a, j+b ) );
                        }
                    }
                }
            }
        }
    // Check for Kings
    } else {
        // flag if the move is a capture
        bool captureFlag = checkCapture( x, y );
        // for each direction
        for ( int a : {-1, 1} ) {
            for ( int b : {-1, 1} ) {
                int i = x + a;
                int j = y + b;
                // move until there is an obstacle on a path
                while ( i >= 0 && j >= 0 && i <= 7 && j <= 7 ) {
                    //if not capturing add those moves
                    if ( cell[i][j].getTYPE() == EMPTY ) {
                        if ( !captureFlag )
                            moves.push_back( Move( x, y, i, j ) );
														break;
                    } else if ( color ) {
                        // break if an ally on path
                        if ( cell[i][j].getTYPE() == YELLOW_KING || cell[i][j].getTYPE() == YELLOW_PAWN )
                            break;
                        // add all moves possible after a capture
                        else if ( ( cell[i][j].getTYPE() == WHITE_KING || cell[i][j].getTYPE() == WHITE_PAWN ) && captureFlag ) {
                            do {
                                i += a;
                                j += b;
                                if ( i >= 0 && j >= 0 && i <= 7 && j <= 7 ) {
                                    if ( cell[i][j].getTYPE() == EMPTY )
                                        moves.push_back( Move( x, y, i, j ) );
																				if(!checkCapture(i, j)){
																					break;
																				}
                                    else
                                        break;
                                } else
                                    break;
                            } while ( true );
                            break;
                        } else
                            break;
                    } else {
                        // break if an ally on path
                        if ( cell[i][j].getTYPE() == WHITE_KING || cell[i][j].getTYPE() == WHITE_PAWN )
                            break;
                        // add all moves possible after a capture
                        if ( ( cell[i][j].getTYPE() == YELLOW_KING || cell[i][j].getTYPE() == YELLOW_PAWN ) && captureFlag ) {
                            do {
                                i += a;
                                j += b;
                                if ( i >= 0 && j >= 0 && i <= 7 && j <= 7 ) {
                                    if ( cell[i][j].getTYPE() == EMPTY )
                                        moves.push_back( Move( x, y, i, j ) );
																				if(!checkCapture(i, j)){
																					break;
																				}
                                    else
                                        break;
                                } else
                                    break;
                            } while ( true );
                            break;
                        } else
                            break;
                    }
                    i += a;
                    j += b;
                }
            }
        }
    }
    return moves;
}
//
// // capture pawn or king from between those coords
void Board::capture( int x1, int y1, int x2, int y2 ) {
    // mark direction
    int a = (x1<x2)? 1 : -1;
    int b = (y1<y2)? 1 : -1;
    // for all fields through the way
    for ( int i = x1+a, j = y1+b; i != x2 && j != y2; i+=a, j+=b ) {
        // clear it
        cell[i][j].setTYPE(EMPTY);
    }
}
//
// // returns 0 if wrong move, 1 if finished, and 2 if there is still a capture to do
int Board::move( Coords m ) {
    bool color = (cell[m.x1][m.y1].getTYPE() == WHITE_KING || cell[m.x1][m.y1].getTYPE() == WHITE_PAWN) ? 0 : 1;
    return move( m.x1, m.y1, m.x2, m.y2, color );
}

int Board::move( Move m ) {
    // bool color = ( cell[m.coords[0].x1][m.coords[0].y1].getTYPE() == WHITE_KING ||
    //                 cell[m.coords[0].x1][m.coords[0].y1].getTYPE() == WHITE_PAWN ) ? 0 : 1;
    int i{};
    while ( move( m.coords[i] ) == 2 )
        i++;
    return 1;
}

int Board::move( int x1, int y1, int x2, int y2, bool color ) {
    // check if player moved right color
    if ( ( color && (cell[x1][y1].getTYPE() == WHITE_KING || cell[x1][y1].getTYPE() == WHITE_PAWN) ) ||
        ( !color && (cell[x1][y1].getTYPE() == YELLOW_KING || cell[x1][y1].getTYPE() == YELLOW_PAWN) ) ){
        return 0;
    }

    bool captureFlag = false;
    // if given move is in viable moves for that pawn/king
    for ( auto& move : getViableMoves( x1, y1 ) ) {
        if ( move == Move( x1, y1, x2, y2 ) ) {
            // if a move included capture
            if ( checkCapture( color ) ) {
                capture( x1, y1, x2, y2 );
                captureFlag = true;
            }
            cell[x2][y2].setTYPE(cell[x1][y1].getTYPE());
            cell[x1][y1].setTYPE(EMPTY);
            // if there is still a capture for this pawn/king
            if ( captureFlag && checkCapture( x2, y2 ) )
                return 2;
            // if a move ended in a promote
            else if ( ( !color && x2 == 7) || ( color && x2 == 0 ) ){
                if(color){
                    cell[x2][y2].setTYPE(YELLOW_KING);
                }else{
                    cell[x2][y2].setTYPE(WHITE_KING);
                }
            }
            return 1;
        }
    }
    return 0;
}
//
// // returns 0 if game continues 1 if red won, 2 if black won, -1 if tie
int Board::checkState( bool color ) {
    int redPawns{}, blackPawns{}, redKings{}, blackKings{};
    bool redMoves{}, blackMoves{};
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            switch ( cell[i][j].getTYPE() ) {
                case EMPTY:
                    break;
                case WHITE_PAWN:
                    if ( !redMoves )
                        if ( getViableMoves( i, j ).size() != 0 )
                            redMoves = true;
                    redPawns++;
                    break;
                case YELLOW_PAWN:
                    if ( !blackMoves )
                            if ( getViableMoves( i, j ).size() != 0 )
                                blackMoves = true;
                    blackPawns++;
                    break;
                case WHITE_KING:
                    if ( !redMoves )
                        if ( getViableMoves( i, j ).size() != 0 )
                            redMoves = true;
                    redKings++;
                    break;
                case YELLOW_KING:
                    if ( !blackMoves )
                        if ( getViableMoves( i, j ).size() != 0 )
                            blackMoves = true;
                    blackKings++;
                    break;
            }
        }
    }
    if ( ( blackPawns || blackKings ) && ( redPawns || redKings ) && ( ( color && blackMoves ) || ( !color && redMoves ) ) ) {
        if ( blackKings && redKings &&
                blackPawns == blackP &&
                redPawns == redP &&
                blackKings == blackK &&
                redKings == redK ) {
            if ( ++drawCounter == 30 )
                return -1;
            else
                drawCounter = 0;
        }
        blackP = blackPawns;
        redP = redPawns;
        blackK = blackKings;
        redK  = redKings;
        return 0;
    }
    else if ( ( !blackPawns && !blackKings ) || ( color && !blackMoves ) )
        return 1;
    else if ( ( !redPawns && !redKings ) || ( !color && !redMoves ) )
        return 2;
    else
        return 10;
}
//
// // evaluate value of a field
// // pawn 7 points
// // last row + 0
// // semi last row + 1
// // 3rd row + 2
// // > 4th row + 3
// // king 25 points
// // anything almost connected with left or right border + 1 point
// // directly connected +2
// // capture oportunity + 15
int Board::evaluateField( int x, int y ) {
    int score{};
    switch( cell[x][y].getTYPE() ) {
        case EMPTY:
            break;
        case WHITE_PAWN:
            score += 7;
            if ( x > 0 ) {
                score += 2;
                if ( x > 1 ) {
                    score ++;
                    if ( x > 2 )
                        score ++;;
                }
            }
            if ( y < 2 || y > 5 ) {
                score ++;
                if ( y < 1 || y > 6 )
                    score ++;
            }
            score += 15;
            break;
        case YELLOW_PAWN:
            score += 7;
            if ( x < 7 ) {
                score += 2;
                if ( x < 6 ) {
                    score ++;
                    if ( x < 5 )
                        score ++;
                }
            }
            if ( y < 2 || y > 5 ) {
                score ++;
                if ( y < 1 || y > 6 )
                    score ++;
            }
            score += 15;
            break;
        case WHITE_KING:
            score += 25;
            if ( y < 2 || y > 5 ) {
                score ++;
                if ( y < 1 || y > 6 )
                    score ++;
            }
            score += 15;
            break;
        case YELLOW_KING:
            score += 25;
            if ( y < 2 || y > 5 ) {
                score ++;
                if ( y < 1 || y > 6 )
                    score ++;
            }
            score += 15;
            break;
    }
    return score;
}

// returns value depending on game state and sum of field values
int Board::evaluateBoard( bool color, bool side ) {
    switch ( checkState( color ) ) {
        case -1:
            return 0;
        case 0:
            break;
        case 1:
            return side ? -10000 : 10000;
        case 2:
            return side ? 10000 : -10000;
    }
    int black{}, red{};
    for ( int i = 0; i < 8; i++ ) {
        for ( int j = 0; j < 8; j++ ) {
            if ( cell[i][j].getTYPE() == WHITE_KING || cell[i][j].getTYPE() == WHITE_PAWN )
                red += evaluateField( i, j );
            else if ( cell[i][j].getTYPE() != EMPTY )
                black += evaluateField( i, j );
        }
    }
    if ( side )
        return black - red;
    else
        return red - black;
}
