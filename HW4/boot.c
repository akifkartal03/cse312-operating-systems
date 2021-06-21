#include "boot.h"

void initSystem(double blockSize, char *fileName,int fd){
    int fileSize;
    int mb;
    if (blockSize == 0.5)
    {
        fileSize = 2048;
        mb = 2;
    }
    else if (blockSize == 1.0)
    {
        fileSize = 4096;
        mb = 4;
    }
    else if (blockSize == 2.0)
    {
        fileSize = 8192;
        mb = 8;
    }
    else if (blockSize == 4.0)
    {
        fileSize = 16384;
        mb = 16;
    }
    superBlock disk;
    disk.blockSize = blockSize;
    disk.diskSize = mb;
    disk.numberOfEntry = (fileSize*1024) / 32;
    disk.numberOfBlock = fileSize / blockSize;
    strcpy(disk.diskName ,fileName);
    printInfo(disk);
    writeToFile(fd,disk);
}
void printInfo(superBlock disk){
    printf("\n\t****Virtual Disk Has Created!****\n");
    printf("-----------------------------------------------------\n");
    printf("Disk Name: %s\n",disk.diskName);
    printf("Disk Size: %dMB\n",disk.diskSize);
    printf("Block Size: %.1fKB\n",disk.blockSize);
    printf("Max Number of Entry: %d\n",disk.numberOfEntry);
    printf("Number of Block: %d\n",disk.numberOfBlock);
    printf("-----------------------------------------------------\n\n");

}
void writeToFile(int fd,superBlock disk){
    //TODOO!!
    //write(fd,)
}