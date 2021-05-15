#ifndef _PAGE_TABLE_H_
#define _PAGE_TABLE_H_

#include<iostream>
#include <cassert>
#include <cmath>
#include "entry.h"
using namespace std;

class PageTable{
public:
    PageTable(unsigned int frmSize, unsigned int numVr, unsigned int numPh);
    void set(unsigned int address, int value); 
    int get(unsigned int address);
    void printInfo() const;
    bool isPresent(unsigned int address) const;
    void setModified(unsigned int address);
    ~PageTable();
private:
    unsigned int frameSize;
    unsigned int pageSize;
    unsigned int numVirFrame;
    unsigned int numPhysFrame;
    unsigned int numPhys;
    unsigned int numVir;
    unsigned int virtualSize;
    unsigned int physSize;

    Entry *table;
    int getIndex(unsigned int address) const;

};
PageTable::PageTable(unsigned int frmSize, unsigned int numVr, unsigned int numPh)
:frameSize(frameSize),numVir(numVr),numPhys(numPh),pageSize(pow(2,frmSize)),numVirFrame(pow(2,numVr)),numPhysFrame(pow(2,numPh)){
    
    virtualSize = numVirFrame*pageSize;
    virtualSize = numPhysFrame*pageSize;
    table = new Entry[numVirFrame];

}
int PageTable::getIndex(unsigned int address) const{
    return address / pageSize;
}
void PageTable::set(unsigned int address, int value){
    assert(address < virtualSize);
    int realIndex = getIndex(address);
    table[realIndex].pageFrameNumber = value;
    if (value >= numPhys )
    {
        table[realIndex].present = false;
    }
    else{
        table[realIndex].present = true;
    }
    table[realIndex].modified = false;
    table[realIndex].referenced = false;
}
int PageTable::get(unsigned int address){
    assert(address < virtualSize);
    return table[getIndex(address)].pageFrameNumber;
} 
void PageTable::printInfo() const{
    cout << "------------Page Table----------------" << endl;
    for (int i = 0; i < numVirFrame; i++)
    {
        Entry temp = table[i];
        cout << "[index: "  << i+1 << "|";
        cout << "modified: "  << temp.modified << "|";
        cout << "present: "  << temp.present << "|";
        cout << "frame number: "  << temp.pageFrameNumber << "]" << endl;
    }
    cout << "-------------------------------------" << endl;
    

}
bool PageTable::isPresent(unsigned int address) const{
    assert(address < virtualSize);
    return table[getIndex(address)].isPresent();
}
void PageTable::setModified(unsigned int address){
    assert(address < virtualSize);
    return table[getIndex(address)].setModified(true);
}

PageTable::~PageTable()
{
    delete[] table;
}

#endif