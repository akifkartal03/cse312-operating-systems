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
    char fileName[8]; //8 byte
    char extension[3]; // 3 byte
    char attributes; // 1 byte
    char reserved[10]; //10 byte
    char time[2]; // 2 byte
    char date[2]; // 2 byte
    char firstBlockNumber[2]; // 2 byte
    unsigned int fileSize; // 4 byte
}entry;


void createFile(double blockSize, char *fileName);
int openFile(char *fileName);
void initSystem(double blockSize, char *fileName,int fileSize, int byteSize);
void printInfo();


#endif