#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>
#include<sys/types.h> 
#include<string.h>
#include<sys/wait.h>
#include <errno.h>
#define TRUE 1

int n = 0; int pid;
char *argv[];char temp[256];
int argc;

void type_prompt()
{	
   printf("[shell-PID=%i]$ ", getpid());
}

void read_command(char *argv[])
{	
   n = 0;
   gets(temp);
   argv[n++] = strtok (temp," ");
   while (argv[n-1] != NULL)
   argv[n++] = strtok (NULL, " ");
}

int main()
{
   int status;
   argv[0] = NULL;
   while (TRUE) /* repeat forever */ {
      type_prompt(); /* display prompt on screen */
      read_command(argv); /* read input from terminal */
      if ((pid = fork()) != 0) /* fork off child process */ {
         printf("Esperando o filho: pid = %i\n", pid);
         waitpid(-1, &status, 0); /* wait for child to exit */
         printf("Waiting finished");
      } 
      else {
         if (execvp(argv[0], argv) == -1) /* execute command */
            printf("Não executou. Erro: %s\n", strerror(errno));
      }
   }
   return 0;
}