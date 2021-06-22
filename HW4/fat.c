#include "fat.h"


int *fat = NULL;
int capacity = 0;

void createFat(int blockSize){
    capacity = 18 * blockSize;
    fat = (int*)calloc(capacity, sizeof(int));
}
void setFat(int index,int value){
    if(index >= capacity || index < 0){
        printf("fat index out of error!\n");
        exit(EXIT_FAILURE);
    }
    fat[index] = value;
}
int getFat(int index){
     if(index >= capacity || index < 0){
        printf("fat index out of error!\n");
        exit(EXIT_FAILURE);
    }
    return fat[index];
}
void destroyFat(){
    if (fat != NULL){
        free(fat);
    }
}