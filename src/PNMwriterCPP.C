#include "PNMwriterCPP.h"
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>

using std::cerr;
using std::endl;
using std::ofstream;

void PNMwriterCPP::Write(char *filename)
{
    ofstream f;
    f.open(filename);
    
    if (f.fail())
    {
        cerr <<  "Unable to open file" << filename << endl;
        exit(EXIT_FAILURE);
    }

    f << "P6\n" << image1->GetWidth() << " " << image1->GetHeight() << endl << 255;
    
    f.write((char *)image1->GetBuffer(), 3 * image1->GetWidth() * image1->GetHeight());

    f.close();
}