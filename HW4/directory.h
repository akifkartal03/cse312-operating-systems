#ifndef _DIRECTORY_ENTRY_H_
#define _DIRECTORY_ENTRY_H_

#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
#include <errno.h>
#include <stdint.h>




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




#endif