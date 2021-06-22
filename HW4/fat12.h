#ifndef _FAT12_H_
#define _FAT12_H_
#include "data_structures.h"

void createFile(double blockSize, char *fileName);
int openFile(char *fileName);
void initSystem(int fd, float blockSize, char *fileName);
void printInfo(superBlock disk);
void writeToFile(int fd,superBlock disk);


#endif