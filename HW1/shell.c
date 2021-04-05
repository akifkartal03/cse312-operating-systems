#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<sys/types.h> 
#include<string.h>
#include<sys/wait.h>
#include <errno.h>
/* a shell program that will be very similar to 
*  the example given in the textbook in Fig 1-19. 
*/
#define TRUE 1
int pid;
char *argv[12];
char filename[41];
char *symbol = "Shell> ";
char *buffer = filename;
size_t bufsize = 41 ,size;

void type_prompt()
{
   //wait a command sign. 	
   printf("%s",symbol);
}

void read_command(char *argv0, char *argv[])
{	
   int n =0;
   size = getline(&buffer,&bufsize,stdin);
   filename[size-1] = '\0';
   if (strcmp(filename,"exit") == 0)
   {
      exit(0);
   }
   argv[n++] = strtok (filename," ");
   while (argv[n-1] != NULL)
      argv[n++] = strtok (NULL, " ");
   argv0 = argv[0]; 
}

int main()
{
   int status;
   argv[0] = NULL;
   while (TRUE) /* repeat forever */ {
      type_prompt(); /* display prompt on screen */
      read_command(argv[0],argv); /* read input from terminal */
      if ((pid = fork()) != 0) /* fork off child process */ {
          /* Parent code. */
         waitpid(-1, &status, 0); /* wait for child to exit */
      } 
      else {
          /* Child code. */
         if (execvp(argv[0], argv) == -1) /* execute command */
            printf("Exec error: %s\n", strerror(errno));
      }
   }
   return 0;
}