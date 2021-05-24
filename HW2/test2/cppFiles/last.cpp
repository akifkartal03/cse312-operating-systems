#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// number of elements in array
// number of threads

int MAX;
int THREAD_MAX;
// array bellow is to store the right edge of a divided array
int index[20] = {0};
int p_i = 0;

using namespace std;

int *a;
int part = 0;
// merge function for merging two parts
void merge(int l1, int h1, int h2) {
    int count = h2 - l1 + 1;
    int sorted[count];
    int i = l1, k = h1 + 1, m = 0;
    while (i <= h1 && k <= h2) {
        if (a[i]<a[k])
            sorted[m++] = a[i++];
        else if (a[k]<a[i])
            sorted[m++] = a[k++];
        else if (a[i] == a[k]) {
            sorted[m++] = a[i++];
            sorted[m++] = a[k++];
        }
    }
    while (i <= h1)
        sorted[m++] = a[i++];

    while (k <= h2)
        sorted[m++] = a[k++];

    int arr_count = l1;
    for (i = 0; i<count; i++, l1++)
        a[l1] = sorted[i];
}

// merge sort function
void merge_sort(int low, int high) {
    // calculating mid point of array
    int mid = low + (high - low) / 2;
    if (low < high) {

        // calling first half
        merge_sort(low, mid);

        // calling second half
        merge_sort(mid + 1, high);

        // merging the two halves
        merge(low, mid, high);
    }
}

// thread function for multi-threading
void* merge_sort(void* arg) {
    int thread_part = part++;

    // calculating low and high
    int low = thread_part * (MAX / THREAD_MAX);
    int high = (thread_part + 1) * (MAX / THREAD_MAX) - 1;

    // allocate the rest part of original array to the last thread
    if(thread_part == THREAD_MAX -1){
        high = MAX - 1;
    }
    // store the right edge of each divided array
    index[++p_i] = high;

    // evaluating mid point
    int mid = low + (high - low) / 2;

    merge_sort(low, mid);
    merge_sort(mid + 1, high);
    merge(low, mid, high);

}
void isSorted(int len) {
    if (len == 1) {
        printf("Sorting Done Successfully\n");
        return;
    }

    int i;
    for (i = 1; i<len; i++) {
        if (a[i]<a[i - 1]) {
            printf("Sorting Not Done\n");
            return;
        }
    }
    printf("Sorting Done Successfully\n");
    return;
}
// Driver Code
int main() {


    /*
    cout << "Enter No of elements of Array:";
    cin >> MAX;

    cout << "Enter No of Thread:";
    cin >> THREAD_MAX;*/

    MAX = 32;
    THREAD_MAX = 12;


    // generating random values in array
    a = new int[MAX];
    srand(time(NULL));
    for (int i = 0; i < MAX; i++) {
        a[i] = rand() % 100;
    }

    // t1 and t2 for calculating time for merge sort

    clock_t t1 = clock();
    pthread_t threads[THREAD_MAX];

    // creating threads
    for (int i = 0; i < THREAD_MAX; i++) {
        pthread_create(&threads[i], NULL, merge_sort, (void*)NULL);
    }


    // joining all threads
    for (int i = 0; i < THREAD_MAX; i++) {
        pthread_join(threads[i], NULL);
    }

    // merging the final parts
    int p = 1;
    int mid, high;
    for(int q = 1; q < THREAD_MAX; q++) {   

        mid = index[p];
        p++;
        high = index[p];
        merge(0, mid, high);            
    }

    clock_t t2 = clock();
    cout << "Time taken: " << (double)(t2 - t1)/ CLOCKS_PER_SEC << endl;
    isSorted(MAX);

    //displaying sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < MAX; i++)
      cout << a[i] << " ";
    cout << endl;
    return 0;
}