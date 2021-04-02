#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <fcntl.h>
#include <errno.h>
int main()
{
    //null termminated arguments
    char *args[]={"./spim", "-file","shellHelp.asm",NULL};
    struct stat buf;
    //check files are exist to run.
    if ((stat("spim", &buf) == 0) && (stat("shellHelp.asm", &buf) == 0))
    {
        if (execvp(args[0],args) == -1) 
            printf("Error!: %s\n", strerror(errno));
    }
    else{
        fprintf(stderr,"File was not found!\n");
        exit(EXIT_FAILURE);
    }
	return 0;
}
