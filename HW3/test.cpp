#include<iostream>
#include "virtual_memory.h"

int main(int argc, char const *argv[])
{
    char arr[20] ="test";
    VirtualMemory vtr(12,5,3,1000);
    vtr.set(3100,2,arr);
    vtr.set(4289,5,arr);
    vtr.set(65897,3,arr);
    //PageTable page(12,4,,,3);
    //page.set(3100,2);
    //page.set(4256,3);
    //page.set(11365,4);

    cout << vtr.get(3100,arr) << endl;
    cout << vtr.get(11365,arr) << endl;
    cout << vtr.get(29896,arr) << endl; 
    cout << vtr.get(65897,arr) << endl; 
    //cout << page.isPresent(3100) << endl;
    //page.setModified(11659);
    //page.printInfo();

    return 0;
}
