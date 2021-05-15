#ifndef _PAGE_TABLE_H_
#define _PAGE_TABLE_H_

#include<iostream>
#include <cassert>
#include "entry.h"
using namespace std;

class PageTable{
public:
    PageTable(unsigned int frmSize, unsigned int numPh, unsigned int numVr);
    void set(unsigned int index, int value); 
    int get(unsigned int index);
    void printInfo() const;
    bool isPresent(unsigned int) const;
    void setModified(unsigned int address);
private:
    unsigned int frameSize;
    unsigned int numPhys;
    unsigned int numVir;
    unsigned int virtualSize;

    Entry *table;
    int getIndex(int adress);

};
PageTable::PageTable(unsigned int frmSize, unsigned int numPh, unsigned int numVr)
:frameSize(frameSize),numVir(numPh),numPhys(numVr){
    
    virtualSize = numVir*frameSize;
    table = new Entry[numVir];

}
int PageTable::getIndex(int adress){
    return adress / frameSize;
}
void PageTable::set(unsigned int index, int value){
    assert(index < numVir*frameSize);
    int realIndex = getIndex(index);
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
int PageTable::get(unsigned int index){
    assert(index < numVir*frameSize);
    return table[getIndex(index)].pageFrameNumber;
} 
void PageTable::printInfo() const{
    cout << "------------Page Table--------------" << endl;
    for (int i = 0; i < numVir; i++)
    {
        Entry temp = table[i];
        cout << "[index: "  << i+1 << "|";
        cout << "modified: "  << temp.modified << "|";
        cout << "present: "  << temp.present << "|";
        cout << "frame number: "  << temp.pageFrameNumber << "]" << endl;
    }
    

}
bool isPresent(unsigned int) ;
void setModified(unsigned int address);

#endif