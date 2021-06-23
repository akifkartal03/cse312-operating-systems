#ifndef _FAT12_H_
#define _FAT12_H_
#include "data_structures.h"

void createFile(double blockSize, char *fileName);
int openFile(char *fileName);
void initSystem(float blockSize, char *fileName);
void printInfo(superBlock disk);


#endif