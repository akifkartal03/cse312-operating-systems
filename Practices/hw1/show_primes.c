#include<stdio.h>
#include<stdlib.h>

int is_prime(int number);
int main(){

    for (int i = 0; i < 1000; i++)
    {
        if (is_prime(i))
        {
            printf("%d(prime)\n",i);
        }
        else{
            printf("%d\n",i);
        }
    }
    return 0;
}
//write as simple as to convert assembly.
int is_prime(int number){
    int counter = 0;
    if (number < 2)
    {
        return 0;
    }
    for (int i = 2; i < number; i++)
    {
        if (number % i == 0)
        {
            counter++;
        }

    }
    if (counter > 0)
    {
        return 0;
    }
    else{
        return 1;
    }

}