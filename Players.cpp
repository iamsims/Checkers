#include "Players.hpp"

Players::Colour Players::getcolour(){return colour;}

TYPE Players::getkey(int a){return key[a];}

void Players::operator()(Colour icolour)
{
        if (icolour==WHITE)
        {
        colour=WHITE;
        key[0]=WHITE_PAWN;
        key[1]=WHITE_KING;
        }

        if (icolour == YELLOW)
        {
        colour=YELLOW;
        key[0]=YELLOW_PAWN;
        key[1]=YELLOW_KING;
        }
}

void Players::operator =(const Players& temp)
{
    this->colour=temp.colour;
    this->key[0]=temp.key[0];
    this->key[1]=temp.key[1];
}
