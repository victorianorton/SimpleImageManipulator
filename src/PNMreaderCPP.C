#include "PNMreaderCPP.h"
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

using std::cerr;
using std::endl;
using std::ifstream;

PNMreaderCPP::PNMreaderCPP(char *filename)
{
    this->filename = filename;
}

void PNMreaderCPP::Execute()
{
    ifstream f;
    f.open(this->filename);
    char magicNum[128];
    int  width, height, maxval;
        
    if (f.fail())
    {
        cerr << "Unable to open filename" << this->filename << endl;
        exit(EXIT_FAILURE);
    }
    
    f >> magicNum >> width >> height >> maxval;
    
    if (strcmp(magicNum, "P6") != 0)
    {
        cerr << "Unable to read from filename, because it is not a PNM filename of type P6" << this->filename << endl;
        exit(EXIT_FAILURE);
    }
    
    img.ResetSize(width, height);
    f.read((char *)img.GetBuffer(), 3 * img.GetWidth() * img.GetHeight());
    
    f.close();
}