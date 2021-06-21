#ifndef _BOOT_SECTOR_H_
#define _BOOT_SECTOR_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
#include <errno.h>
#include <stdint.h>

typedef  uint8_t byte1;	 // 1 byte
typedef  uint16_t  byte2; // 2 bytes
typedef  uint32_t  byte4; // 4 bytes


typedef struct BootSector{
    char diskName[20];
    int diskSize;
    double blockSize;
    int numberOfEntry;
    int numberOfBlock;
    int fatTablePosition;
    int rootDirPosition;
    int dataStartPosition;
}superBlock;

void initSystem(double blockSize, char *fileName,int fd);
void printInfo(superBlock disk);
void writeToFile(int fd,superBlock disk);


#endif