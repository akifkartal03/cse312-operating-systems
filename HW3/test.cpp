#include<iostream>
#include "page_table.h"

int main(int argc, char const *argv[])
{
    
    PageTable page(12,4,3);
    page.set(3100,2);
    page.set(4256,3);
    page.set(11365,4);

    cout << page.get(3100) << endl;
    cout << page.get(11365) << endl;
    cout << page.get(29896) << endl; 
    cout << page.isPresent(3100) << endl;
    page.setModified(11659);
    page.printInfo();

    return 0;
}
