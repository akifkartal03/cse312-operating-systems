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

typedef  uint8_t  byte1;   // 1 byte
typedef  uint16_t  byte2; // 2 bytes
typedef  uint32_t  byte4; // 4 bytes


typedef struct __attribute__ ((__packed__)) BootSector{
    char diskName[13];
    byte4 diskSize;
    float blockSize;
    byte4 numberOfEntry;
    byte4 numberOfBlock;
    byte4 totalByte;
    byte4 fatTablePosition;
    byte4 rootDirPosition;
    byte4 dataStartPosition;
}superBlock;

void initSystem(int fd, float blockSize, char *fileName);
void printInfo(superBlock disk);
void writeToFile(int fd,superBlock disk);


#endif