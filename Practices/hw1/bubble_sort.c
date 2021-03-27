#include <stdio.h>
//write as simple as to convert assembly.
void bubbleSort(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int arr[20];
    int n;
    printf("enter array size: ");
    scanf("%d",&n);
    while (n < 1)
    {
        printf("enter a valid size: ");
        scanf("%d",&n);
    }
    printf("enter numbers one by one!\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    bubbleSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
