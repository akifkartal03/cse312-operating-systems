#ifndef _PART2_H_
#define _PART2_H_

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
#include <errno.h>

typedef struct Boot{
    char *diskName;
    int diskSize;
    double BlockSize;
    int numberOfEntry;

}superBlock;

typedef struct directory{
    char fileName[8];
    char extension[8];
    char attributes;
    char reserved[10];
    char time[2];
    char date[2];
    char firstBlockNumber[2];
    unsigned int fileSize;


}entry;


void createFile(double blockSize, char *fileName);
int openFile(char *fileName);
void initSystem(double blockSize, char *fileName,int fileSize, int byteSize);
void printInfo();


#endif