#ifndef _VIRTUAL_MEMORY_H_
#define _VIRTUAL_MEMORY_H_

#include <iostream>
#include "page_table.h"

using namespace std;

class VirtualMemory
{
public:
    VirtualMemory(unsigned int frmSize, unsigned int numVr, unsigned int numPy, unsigned int interval);
    void set(unsigned int index, int value, char *tName);
    int get(unsigned int index, char *tName);
    ~VirtualMemory();

private:
    unsigned int frameSize;
    unsigned int numPhys;
    unsigned int numVir;
    unsigned int virtualSize;
    unsigned int physicalSize;
    unsigned int printInterval;

    int *memory; //physical memory
    PageTable *pageTable; // virtual memory
};
VirtualMemory::VirtualMemory(unsigned int frmSize, unsigned int numVr, unsigned int numPy, unsigned int interval)
    : frameSize(frmSize), numPhys(numPy), numVir(numVr), printInterval(interval)
{
    virtualSize = pow(2,frameSize) * pow(2,numVir);
    physicalSize = pow(2,frameSize) * pow(2,numPhys);
    memory = new int[physicalSize];

    for (int i = 0; i < physicalSize; i++)
        memory[i] = 0;
    pageTable = new PageTable(frameSize,numVir,numPhys);
    
}


void VirtualMemory::set(unsigned int index, int value, char *tName){
    unsigned int address = pageTable->get(index);
    //cout <<" set adress:" << address << endl;
    memory[address] = value;

}
int VirtualMemory::get(unsigned int index,char *tName){
    unsigned int address = pageTable->get(index);
    //cout <<" get adress:" << address << endl;
    return memory[address];

}

VirtualMemory::~VirtualMemory()
{
    
    delete[] memory;
    delete pageTable;
   
}

#endif