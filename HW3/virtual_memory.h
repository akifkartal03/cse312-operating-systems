#ifndef _VIRTUAL_MEMORY_H_
#define _VIRTUAL_MEMORY_H_

#include<iostream>
using namespace std;

class VirtualMemory{
public:
    void set(unsigned int index, int value, char * tName); 
    int get(unsigned int index, char * tName);
private:
    unsigned int frameSize;
    unsigned int numPhys;
    unsigned int numVir;
    unsigned int virtualSize;
    unsigned int physicalSize;

    /* physical memory */
    int *memory; 


};




#endif