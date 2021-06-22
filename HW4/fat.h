#ifndef _FAT_TABLE_H_
#define _FAT_TABLE_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/file.h>
#include <errno.h>
#include <stdint.h>

extern int *fat;
extern int capacity;

void createFat(int blockSize);
void setFat(int index,int value);
int getFat(int index);
void destroyFat();


#endif