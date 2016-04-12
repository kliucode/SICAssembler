/*
 *  hash.h
 *  ------
 *  Header file containing all the function declaration for the Hash class.
 *
 *  Author: Kaihua Liu
 *  Date Created: 03/30/15
 *  Course: COP3404
 *  Section: 11329
 *
 */

#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;

/*
 *  Creating a struct of nodes to be used for the array
 */
struct node
{
    string key;
    int val1;
    int val2;
    int val3;
    bool emptyFlag = true;
};


class Hash
{
public:
    Hash();
    Hash(int arraySize);
    ~Hash();
    bool put(string key, int val1, int val2, int val3);
    int locate(string key);
    bool contains(string key);
    int getValue1(string key);
    int getValue2(string key);
    int getValue3(string key);
    int getNodeArraySize();
    int getNextAvailableNode();
    void printHashTable();
    node getNodeAt(int loc);

protected:
    bool isEmpty(node testNode);

private:
    int nodeArraySize;
    node* hashTable;
    int nextAvailableNode;


};

#endif // HASH_H
