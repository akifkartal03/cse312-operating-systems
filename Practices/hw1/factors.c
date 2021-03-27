#include<stdio.h>
#include<stdlib.h>
//write as simple as to convert assembly.
int main(){

    int number;
    printf("enter a number: ");
    scanf("%d",&number);
    /*while (number < 1)
    {
        printf("enter a valid number: ");
        scanf("%d",&number);
    }*/
    if (number < 0)
    {
        for (int i = -1; i > number; i--)
        {
            if (number % i == 0){
                printf("%d, ",i);
            }
        }
        printf("%d\n",number);
    }
    else if (number > 0)
    {
        for (int i = 1; i < number; i++)
        {
            if (number % i == 0){
                printf("%d, ",i);
            }
        }
        printf("%d\n",number);

    }
    else{
        printf("No value\n");
    }
    return 0;
}
