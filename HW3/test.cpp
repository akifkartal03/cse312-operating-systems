#include<iostream>
#include "entry.h"

int main(int argc, char const *argv[])
{
    
    Entry entr;

    cout << entr.getFrameNumber() << endl;
    cout << entr.isPresent() << endl;
    return 0;
}
