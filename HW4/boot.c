#include "boot.h"

#include "directory.h"


void initSystem(int fd, float blockSize, char *fileName){
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
    disk.totalByte = fileSize*1024;
    strcpy(disk.diskName ,fileName);
    writeToFile(fd,disk);
    printInfo(disk);
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
void writeToFile(int fd, superBlock disk){
    //TODOO!!
    //write(fd,)
    uint8_t filesystem[(1024*1024)*2] = {0};
    superBlock *s = (superBlock *)filesystem;
    s->blockSize = disk.blockSize;
    s->diskSize = disk.diskSize;
    s->numberOfEntry = disk.numberOfEntry;
    s->numberOfBlock = disk.numberOfBlock;
    s->fatTablePosition= disk.totalByte - (disk.totalByte - sizeof(superBlock) + 1);
    s->rootDirPosition= disk.totalByte - (disk.totalByte - sizeof(superBlock) - (18 * disk.blockSize*1024));
    s->dataStartPosition= s->rootDirPosition + sizeof(entry) + 1;
    strcpy(s->diskName,disk.diskName);
    entry rootDir;
    rootDir.attributes = 0;
    strcpy(rootDir.fileName,"/");
    rootDir.firstBlockNumber = s->dataStartPosition;
    printf("Disk Name: %s\n",s->diskName);
    printf("Disk Size: %dMB\n",s->diskSize);
    printf("Block Size: %.1fKB\n",s->blockSize);
    printf("Max Number of Entry: %d\n",s->numberOfEntry);
    printf("Number of Block: %d\n",s->numberOfBlock);
    printf("fat: %d\n",s->fatTablePosition);
    printf("root: %d\n",s->rootDirPosition);
    printf("data: %d\n",s->dataStartPosition);
    printf("sizeof: %d\n",sizeof(entry));
    printf("sizeof2: %d\n",sizeof(superBlock));
    printf("total: %d\n",disk.totalByte);
    write(fd, filesystem, sizeof(filesystem));

}