/*
 *  assemblerpass1.h
 *  ----------------
 *  Header file containing all the function declaration for the AssemblerPass1 class.
 *
 *  Author: Kaihua Liu
 *  Date Created: 03/30/15
 *  Course: COP3404
 *  Section: 11329
 *
 */

#ifndef ASSEMBLERPASS1_H
#define ASSEMBLERPASS1_H

#include "hash.h"

#include <iostream>
#include <fstream>
#include <string>
using std::sscanf;
using std::cerr;
using std::endl;
using std::cin;
using std::cout;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::string;


class AssemblerPass1
{
public:
    AssemblerPass1();
    AssemblerPass1(char* opFile, char* symFile);
    ~AssemblerPass1();
    void run();
    bool extract(string line, char* label, char* opcode, char* operand);
    void printSymbolTable();

private:
    bool buildOpTab();
    bool processProgram();
    void outputLine(char *display);
    void outputLine(int errorFlag, char *display);
    int getLineCount(ifstream* inputFile);
    bool isWhiteSpace(char character);
    ifstream optabFile, symtabFile;
    ofstream outFile;
    Hash opTab, symTab;
    int startAddress;
    int locctr;
};

#endif // ASSEMBLERPASS1_H
