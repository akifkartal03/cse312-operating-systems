#include "fat12.h"


int *fat = NULL;
int capacity = 0;
byte1 *freeBlocksBitmap = NULL;
entry *directories = NULL;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Arguments are wrong!!\n");
        exit(EXIT_FAILURE);
    }
    float blockSize = atof(argv[1]);
    createFile(blockSize,argv[2]);
    return 0;
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

void createFile(double blockSize, char *fileName){
    int fileSize;
    if (blockSize == 0.50)
    {
        fileSize = 2048;
    }
    else if (blockSize == 1.0)
    {
        fileSize = 4096;
    }
    else if (blockSize == 2.0)
    {
        fileSize = 8192;
    }
    else if (blockSize == 4.0)
    {
        fileSize = 16384;
    }
    else{
        printf("Wrong block Size, Try Again!\n");
        exit(EXIT_FAILURE);
    }
    int fd = openFile(fileName);
    ftruncate(fd, fileSize*1024);
    initSystem(fd,blockSize, fileName);
    
}


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
    disk.bootSectorPosition = 0;
    disk.fatTablePosition= disk.totalByte - (disk.totalByte - sizeof(superBlock)) + 1 ;
    disk.rootDirPosition= disk.totalByte - (disk.totalByte - sizeof(superBlock) - (18 * disk.blockSize*1024));
    disk.dataStartPosition= disk.rootDirPosition + sizeof(entry) + 1;
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
    printf("Number of Block: %d\n",disk.numberOfBlock);
    printf("Boot Sector Start Adress: %d\n",disk.bootSectorPosition);
    printf("FAT Table Start Adress: %d\n",disk.fatTablePosition);
    printf("Root Directory Start Adress: %d\n",disk.rootDirPosition);
    printf("Data Region Start Adress: %d\n",disk.dataStartPosition);
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
    s->bootSectorPosition= disk.bootSectorPosition;
    s->fatTablePosition= disk.fatTablePosition;
    s->rootDirPosition= disk.rootDirPosition;
    s->dataStartPosition= disk.dataStartPosition;
    strcpy(s->diskName,disk.diskName);
    entry rootDir;
    rootDir.attributes = 0;
    strcpy(rootDir.fileName,"/");
    rootDir.firstBlockNumber = s->dataStartPosition;
    write(fd, filesystem, sizeof(filesystem));

}