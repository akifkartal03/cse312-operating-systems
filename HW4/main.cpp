#include "main.h"

int *fat = NULL;
superBlock disk;
entry *directories = NULL;
void createFile(double blockSize, char *fileName){
    int fileSize;
    int mb;
    if (blockSize == 0.50)
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
    else{
        printf("Wrong block Size, Try Again!\n");
        exit(EXIT_FAILURE);
    }
    int fd = openFile(fileName);
    ftruncate(fd, fileSize*1024);
    initSystem(blockSize, fileName,mb, fileSize*1024);
    
    
}
int openFile(char *fileName){
    int fd = open(fileName, O_RDWR|O_CREAT|O_EXCL, 0666);
    if(fd < 0) {
        if (errno == EEXIST){
            remove(fileName);
            return openFile(fileName);
        }
        exit(EXIT_FAILURE);
    }
    return fd;
}
void initSystem(double blockSize, char *fileName,int fileSize, int byteSize){
    disk.BlockSize = blockSize;
    disk.diskSize = fileSize;
    disk.numberOfEntry = byteSize / 32;
    disk.diskName = fileName;
}
void printInfo(){
    printf("\t****Virtual Disk Has Created!****\n");
    printf("-----------------------------------------------------\n");
    printf("Disk Name: %s\n",disk.diskName);
    printf("Disk Size: %dMB\n",disk.diskSize);
    printf("Block Size: %.1fKB\n",disk.BlockSize);
    printf("Max Number of Entry: %d\n",disk.numberOfEntry);
    printf("-----------------------------------------------------\n");

}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Arguments are wrong!!\n");
        exit(EXIT_FAILURE);
    }
    double blockSize = atof(argv[1]);
    char *fileName = argv[2];
    createFile(blockSize,fileName);
    printInfo();
    return 0;
}