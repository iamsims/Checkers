#pragma once
#include"Cell.hpp"

class Players
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
    //TYPE& setktype(int);
    void operator = (const Players& temp);


private:
  //  ENUM colour  use enum to do
  //  {
  //  }      //add a member tot no. of figures...and modify the code in
    TYPE key[2];
    Colour colour;
    //friend class Board;


};

