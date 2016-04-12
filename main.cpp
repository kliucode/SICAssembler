/*
 *  main.cpp
 *  --------
 *  Driver program for AssemblerPass1.
 *
 *  Author: Kaihua Liu
 *  Date Created: 03/30/15
 *  Course: COP3404
 *  Section: 11329
 *
 */

#include "assemblerpass1.h"
#include <iostream>
using std::cerr;

int main(int argc, char* argv[])
{
    AssemblerPass1* pass1;

    if(argc < 3)
    {
        char* opFile = new char[100];
        char* symFile = new char[100];

        cout<<"Object Code Reference File: ";
        cin >> opFile;
        cout<<"Symbol File: ";
        cin >> symFile;

        pass1 = new AssemblerPass1(opFile, symFile);
    }
    else
    {
        pass1 = new AssemblerPass1(argv[1], argv[2]);
    }

    pass1->run();

    return 0;
}
