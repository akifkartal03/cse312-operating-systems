#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

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
    char diskName[20];
    byte4 diskSize;
    float blockSize;
    byte4 numberOfEntry;
    byte4 numberOfBlock;
    byte4 totalByte;
    byte4 bootSectorPosition;
    byte4 fatTablePosition;
    byte4 rootDirPosition;
    byte4 dataStartPosition;
}superBlock;


typedef struct __attribute__ ((__packed__)) directory{
    char fileName[8]; //8 byte
    char extension[3]; // 3 byte
    byte1 attributes; // 1 byte
    char reserved[10]; //10 byte
    byte2 time; // 2 byte
    byte2 date; // 2 byte
    byte2 firstBlockNumber; // 2 byte
    byte4 fileSize; // 4 byte
}entry;

extern int *fat;
extern int capacity;
extern byte1 *freeBlocksBitmap; //bitmap array to keep free block information
extern entry *directories; // all directrioes in file system

#endif