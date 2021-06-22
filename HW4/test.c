#include "boot.h"

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