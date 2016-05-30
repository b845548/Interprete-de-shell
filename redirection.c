#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
 	

#include <fcntl.h>
# include <sys/types.h>
int             main(int ac, char *av[], char *envp[])
{
  int   ret;
  int   n;
 
  ret = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
 
  if (ret == -1)
    {
      puts("Error open ....");
      exit(EXIT_FAILURE);
    }
  dup2(ret, 1);
  execlp("ls", "ls", (char *)0);
 
  close(ret);
  return (1);
}
