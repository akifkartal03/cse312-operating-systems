#ifndef _ENTRY_H_
#define _ENTRY_H_

#include<iostream>
using namespace std;

class Entry{
    friend class PageTable;
public:
    Entry();

    unsigned int getFrameNumber() const;
    bool isReferenced() const;
    bool isModified() const;
    bool isPresent() const;

    void setReferenced(bool);
    void setModified(bool);
    void setPresent(bool);
    void setPageFrameNumber(unsigned int frmNumber);
    
private:
    bool referenced;
    bool modified;
    bool present;
    unsigned int pageFrameNumber;
    
};

Entry::Entry(){
    referenced = false;
    modified = false;
    present = false;
    pageFrameNumber = 0;
}
bool Entry::isReferenced() const
{
    return referenced;
}

bool Entry::isModified() const
{
    return modified;
}

unsigned int Entry::getFrameNumber() const
{
    return pageFrameNumber;
}

void Entry::setReferenced(bool val)
{
    referenced = val;
}
void Entry::setModified(bool val)
{
    modified = val;
}

void Entry::setPresent(bool present)
{
    present = present;
}

bool Entry::isPresent() const
{
    return present;
}
void Entry::setPageFrameNumber(unsigned int frmNumber)
{
    pageFrameNumber = frmNumber;
}


#endif