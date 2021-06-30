#include<iostream>
#include "virtual_memory.h"

int main(int argc, char const *argv[])
{
    char arr[20] ="test";
    VirtualMemory vtr(12,10,5,1000); //create virtual memory
    vtr.set(3100,2,arr);
    vtr.set(4289,5,arr);
    vtr.set(65897,3,arr);
    

    cout << "Data in 3100: " << vtr.get(3100,arr) << endl;
    cout << "Data in 11365: " << vtr.get(11365,arr) << endl;
    cout << "Data in 29896: " << vtr.get(29896,arr) << endl; 
    cout << "Data in 65897: " << vtr.get(65897,arr) << endl; 
    
    return 0;
}

