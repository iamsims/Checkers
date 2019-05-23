#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Cell.hpp"

class Player
{

public:
     enum Colour
    {
        EMPTY,
        WHITE,
        YELLOW
    };
    Colour getcolour();
    void operator ()(Colour icolour);
    TYPE getkey(int );
    void operator = (const Player& temp);

private:
    TYPE key[2];
    Colour colour;
};
#endif
