#include "Board.hpp"

Board::Board(){
    player1(Players::WHITE);
    player2(Players::YELLOW);
	initBoard();
};

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
        return 1;
    }

    else return 0;
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
    int newstate =cell[xCoordSelectedCell+Xdisplacement][yCoordSelectedCell+Ydisplacement].getTYPE();
    int oldstate=cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE();

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

      return valid;

}


void Board::Move(int newX, int newY)
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
    }
    else isMoving=0;

}


void Board::update( )
{
 if (cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()== WHITE_PAWN && xCoordSelectedCell==7)
   cell[xCoordSelectedCell][yCoordSelectedCell].setTYPE(WHITE_KING);

 if (cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()== YELLOW_PAWN && xCoordSelectedCell==0)
    cell[xCoordSelectedCell][yCoordSelectedCell].setTYPE(YELLOW_PAWN);

}


bool Board::multipleMoveValid()
{
    if (isMoving)
    {
        if (cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()==WHITE_KING ||cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()==WHITE_PAWN )
        {
            if (cell[xCoordSelectedCell+1][yCoordSelectedCell-1].getTYPE()==YELLOW_KING || cell[xCoordSelectedCell+1][yCoordSelectedCell-1].getTYPE()==YELLOW_PAWN||
                cell[xCoordSelectedCell+1][yCoordSelectedCell+1].getTYPE()==YELLOW_KING || cell[xCoordSelectedCell+1][yCoordSelectedCell+1].getTYPE()==YELLOW_PAWN ||
                cell[xCoordSelectedCell-1][yCoordSelectedCell-1].getTYPE()==YELLOW_KING || cell[xCoordSelectedCell-1][yCoordSelectedCell-1].getTYPE()==YELLOW_PAWN ||
                cell[xCoordSelectedCell-1][yCoordSelectedCell+1].getTYPE()==YELLOW_KING || cell[xCoordSelectedCell-1][yCoordSelectedCell+1].getTYPE()==YELLOW_PAWN )
                return true;
        }

        if (cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()==YELLOW_KING ||cell[xCoordSelectedCell][yCoordSelectedCell].getTYPE()==YELLOW_PAWN )
        {
            if (cell[xCoordSelectedCell+1][yCoordSelectedCell-1].getTYPE()==WHITE_KING || cell[xCoordSelectedCell+1][yCoordSelectedCell-1].getTYPE()==WHITE_PAWN||
                cell[xCoordSelectedCell+1][yCoordSelectedCell+1].getTYPE()==WHITE_KING || cell[xCoordSelectedCell+1][yCoordSelectedCell+1].getTYPE()==WHITE_PAWN||
                cell[xCoordSelectedCell-1][yCoordSelectedCell-1].getTYPE()==WHITE_KING || cell[xCoordSelectedCell-1][yCoordSelectedCell-1].getTYPE()==WHITE_PAWN||
                cell[xCoordSelectedCell-1][yCoordSelectedCell+1].getTYPE()==WHITE_KING || cell[xCoordSelectedCell-1][yCoordSelectedCell+1].getTYPE()==WHITE_PAWN )
                return true;
        }
    }

    return false;
}



bool Board::checkStaleMate()   // return 0 if not stalemate and 1 if stalemate
{
    int Xbackup=xCoordSelectedCell, Ybackup=yCoordSelectedCell;

    for (int i =0;i<8;i++)
    {
    for (int j =0;j<8;j++)
    {if (cell[i][j].getTYPE()==0)continue;
    selectCell(i,j);
    for (int k =i-2;k<i+2;k++)
    {
        for (int l =j-2;l<j+2;l++)
        {
            if (isValidMove(k,l))
            {
               selectCell(Xbackup,Ybackup);
               return 0;

            }
        }
    }
    }
    }
    selectCell(Xbackup,Ybackup);
    return 1;
}


bool Board::checkWin()
{
     int nOpponents=0;

    for (int i =0;i<8;i++)
    {
        for (int j =0;j<8;j++)
        {
            if (currentPlayer.getcolour() ==Players::Colour::YELLOW)
            if (cell[i][j].getTYPE()==WHITE_PAWN || cell[i][j].getTYPE()==WHITE_KING)
                nOpponents++;


            if (currentPlayer.getcolour()==Players::Colour::WHITE)
            if (cell[i][j].getTYPE()==YELLOW_PAWN || cell[i][j].getTYPE()==YELLOW_KING)
                nOpponents++;
        }
    }

    if (nOpponents=0) return 1;
    else return 0;

}
