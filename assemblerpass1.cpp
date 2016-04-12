/*
 *  assemblerpass1.cpp
 *  ------------------
 *  This file contains all the implementations for the simulation of AssemblerPass1.
 *  This program will read a text file of SIC OPCODE as reference and a SIC program
 *  and generate appropriate intermediate file with calculated addresses. The
 *  intermediate file is generated and stored as a text file.
 *
 *  Author: Kaihua Liu
 *  Date Created: 03/30/15
 *  Course: COP3404
 *  Section: 11329
 *
 */


#include "assemblerpass1.h"

AssemblerPass1::AssemblerPass1()
{
    cerr<<"No Arguments Provided. Invalid State. Terminating!"<<endl;
}

AssemblerPass1::AssemblerPass1(char *opFile, char *symFile)
    :optabFile(opFile, ios::in),
      symtabFile(symFile, ios::in),
        outFile("results.txt", ios::out)
{
    if(!optabFile)
    {
        cerr<<"File "<<opFile<< " could not be opened. \nTerminating"<<endl;
        exit(1);
    }

    if(!symtabFile)
    {
        cerr<<"File "<<symFile<< " could not be opened. \nTerminating"<<endl;
        exit(1);
    }

    locctr = 0;
}

AssemblerPass1::~AssemblerPass1()
{

}


void AssemblerPass1::run()
{
    if(buildOpTab())
    {
       cout<<"OPTAB Build Successfully!"<<endl;
    }
    else
    {
        cerr<<"ERROR! Fail to Build OPTAB!"<<endl;
        exit(1);
    }

    processProgram();
    printSymbolTable();
}

bool AssemblerPass1::buildOpTab()
{
    opTab = Hash(getLineCount(&optabFile));

    string line;
    char code[100];
    int opcode, format, mem;

    while(getline(optabFile, line))
    {
        code[0] = '\0';
        opcode = format = mem = 0;
        sscanf(line.c_str(), "%s\t%x\t%d\t%d", code, &opcode, &format, &mem);
        opTab.put(string(code), opcode, format, mem);
    }

    return true;

}

bool AssemblerPass1::processProgram()
{
    symTab = Hash(100);

    string line = "";
    char label[100];
    char code[100];
    char operand[100];
    char output[200];

    getline(symtabFile, line);
    extract(line, label, code, operand);

    if(strcmp(code, "START")==0)
    {
        int i = 0;
        sscanf(operand, "%x", &i);
        startAddress = i;
        locctr = i;
        sprintf(output, "%x\t%s\t%s\t%s", locctr, label, code, operand);
        outputLine(output);
        getline(symtabFile, line);
        extract(line, label, code, operand);
        output[0] = '\0';
    }
    else
    {
        locctr = 0;
    }

    while(!strcmp(code, "END")==0)
    {
        if(line[0] != '.')
        {
            if(strlen(label) != 0)
            {
                if(!symTab.locate(label))
                 {
                    sprintf(output, "Duplicate Symbol \"%s\" Found!", label);
                 }
                 else
                 {
                    symTab.put(label, locctr, 0, 0);
                 }

                 if(opTab.locate(code)!= -1)
                 {
                    if(opTab.getValue2(code) != -1)
                    {
                        sprintf(output, "%x\t%s%\t%s\t%s", locctr, label, code, operand);
                        locctr += opTab.getValue2(code);
                    }
                 }
                 else if(strcmp(code, "RESW")==0)
                 {
                    sprintf(output, "%x\t%s%\t%s\t%s", locctr, label, code, operand);
                    int reserve = 0;
                    sscanf(operand, "%d", &reserve);
                    locctr += (3*reserve);
                 }
                 else if(strcmp(code, "RESB")==0)
                 {
                    sprintf(output, "%x\t%s%\t%s\t%s", locctr, label, code, operand);
                    int reserve = 0;
                    sscanf(operand, "%d", reserve);
                    locctr += reserve;
                 }else if(strcmp(code, "BYTE")==0)
                 {
                    sprintf(output, "%x\t%s%\t%s\t%s", locctr, label, code, operand);
                    int operandSize = (unsigned)strlen(operand);
                    locctr += operandSize;
                 }else if((strcmp(code, "BASE")==0))
                 {
                     sprintf(output, "%x\t%s%\t%s\t%s", locctr, label, code, operand);
                 }else if(strcmp(code, "WORD")==0)
                 {
                      sprintf(output, "%x\t%s%\t%s\t%s", locctr, label, code, operand);
                      locctr += 3;
                 }
                 else
                 {
                    sprintf(output, "Invalid OPCODE \"%s\"!", code);
                 }
            }
            outputLine(output);
        }
        else
        {
            sprintf(output, "%s", line.c_str());
            outputLine(output);
        }

        getline(symtabFile, line);
        extract(line, label, code, operand);
        output[0] = '\0';

    }

    if(strcmp(code, "END")==0)
    {
        sprintf(output, "%x\t%s%\t%s\t%s", locctr, label, code, operand);
        outputLine(output);
        output[0] = '\0';
    }

    return true;

}


void AssemblerPass1::outputLine(char* display)
{
     outFile<<display<<endl;
}

int AssemblerPass1::getLineCount(ifstream* inputFile)
{
    int count = 0;
    string line;
    while(!inputFile->eof())
    {
        getline(*inputFile, line);
        count++;
    }

    inputFile->seekg(0);                            //resets the cursor to the beginning of the file

    return count;
}

bool AssemblerPass1::extract(string line, char* label, char* opcode, char* operand)
{
    label[0] = '\0';
    opcode[0] = '\0';
    operand[0] = '\0';
    int i = 0;
    int j = 0;
    int leadingWhiteCount = 0;

    while(isWhiteSpace(line[i]))
    {
        i++;
        leadingWhiteCount++;
        if(i > line.length())
            return false;
    }
    if(leadingWhiteCount < 5)
    {while(!isWhiteSpace(line[i]))
    {
        label[j] = line[i];
        i++; j++;
        if(i > line.length())
            return false;
    }
    label[j] = '\0';
    j = 0;
    }
    while(isWhiteSpace(line[i]))
    {
        i++;
        if(i > line.length())
            return false;
    }
    while(!isWhiteSpace(line[i]))
    {
        opcode[j] = line[i];
        i++; j++;
        if(i > line.length())
            return false;
    }
    opcode[j] = '\0';
    j = 0;
    while(isWhiteSpace(line[i]))
    {
        i++;
        if(i > line.length())
            return false;
    }
    while(!isWhiteSpace(line[i]))
    {
        operand[j] = line[i];
        i++; j++;
        if(i > line.length())
            return false;
    }
    operand[j] = '\0';

    return true;


}

bool AssemblerPass1::isWhiteSpace(char character)
{
    if(character == ' ' || character == '\t')
    {
        return true;
    }

    return false;
}

void AssemblerPass1::printSymbolTable()
{
    char output[200];

    sprintf(output,"\n\n\n\nTable Loc\tLabel\tAddress");
    outputLine(output);

    for(int i = 0; i < symTab.getNextAvailableNode(); i++)
    {
        sprintf(output, "%d\t\t%s\t%x", i, symTab.getNodeAt(i).key.c_str(), symTab.getNodeAt(i).val1);
        outputLine(output);
    }



}

