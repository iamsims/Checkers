#include <fstream>
#include <iostream>
#include"Board.hpp"

fstream myfile;

_Board loadfromfile ()
{
    _Board _fboard;
    ifstream input_file("data.dat", ios::binary);
    input_file.read((char*)&_fboard, sizeof(_fboard));
    input_file.close();
    return _fboard;

}

void savetofile(_Board _fboard)
{
    ofstream output_file("data.dat", ios::binary);
    output_file.write((char*)&_fboard, sizeof(_fboard));
    output_file.close();

}
