/*
 *  hash.cpp
 *  --------
 *  This file contains all the implementations for the Hash object.
 *  The functions are cabable of hashing a key and a value. Also locating
 *  a key on the array. This file has been improved in terms of performance
 *  and functionality from Project 1.
 *
 *  Author: Kaihua Liu
 *  Date Created: 03/30/15
 *  Course: COP3404
 *  Section: 11329
 *
 */

#include "hash.h"

Hash::Hash()
{

}

Hash::Hash(int arraySize)
{
    nodeArraySize = arraySize;
    hashTable = new node[arraySize];
    nextAvailableNode = 0;
}

Hash::~Hash()
{

}

bool Hash::put(string key, int val1, int val2, int val3)
{
    if(contains(key))
    {
        return false;
    }

    hashTable[nextAvailableNode].key = key;
    hashTable[nextAvailableNode].val1 = val1;
    hashTable[nextAvailableNode].val2 = val2;
    hashTable[nextAvailableNode].val3 = val3;
    hashTable[nextAvailableNode].emptyFlag = false;

    nextAvailableNode++;

    return true;

}

int Hash::locate(string key)
{
    for(int i = 0; i < nodeArraySize; i++)
    {
        if(hashTable[i].key == key)
        {
            return i;
        }
    }

    return -1;
}

bool Hash::contains(string key)
{
    for(int i = 0; i < nodeArraySize; i++)
    {
        if(hashTable[i].key == key)
        {
            return true;
        }
    }

    return false;
}

 int Hash::getValue1(string key)
 {
     if(contains(key))
     {
         return (hashTable[locate(key)].val1);
     }

     return -1;
 }

 int Hash::getValue2(string key)
 {
     if(contains(key))
     {
         return (hashTable[locate(key)].val2);
     }

     return -1;
 }

 int Hash::getValue3(string key)
 {
     if(contains(key))
     {
         return (hashTable[locate(key)].val3);
     }

     return -1;

 }

bool Hash::isEmpty(node testNode)
{
    return(testNode.emptyFlag);
}

int Hash::getNodeArraySize()
{
    return nodeArraySize;
}

int Hash::getNextAvailableNode()
{
    return nextAvailableNode;
}

void Hash::printHashTable()
{
    cout<<"Printing Hash Table: "<<endl;
    for(int i = 0; i < nextAvailableNode; i++)
    {
        cout<<hashTable[i].key<<" "<<hashTable[i].val1<<" "<<hashTable[i].val2<<" "<<hashTable[i].val3<<" "<<hashTable[i].emptyFlag<<endl;
    }
}

node Hash::getNodeAt(int loc)
{
    return hashTable[loc];
}
