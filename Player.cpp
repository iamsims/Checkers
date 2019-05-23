#include "Player.hpp"

Player::Colour Player::getcolour(){return colour;}

TYPE Player::getkey(int a){return key[a];}

void Player::operator()(Colour icolour)
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

void Player::operator =(const Player& temp)
{
    this->colour=temp.colour;
    this->key[0]=temp.key[0];
    this->key[1]=temp.key[1];
}
