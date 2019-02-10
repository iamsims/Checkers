#include "Cell.hpp"

Cell::Cell() : _type(EMPTY){};

TYPE Cell::getTYPE() const{
	return _type;
};

void Cell::setTYPE(TYPE type)
{
    _type = type;
}
