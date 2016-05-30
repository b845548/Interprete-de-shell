#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define MaxPathLength 1024
/*

  l'objectif de ce programme est d'excuter plusieurs Pipe
  apparement on en a pas encore reussi 


 */
char * dirs_[] ={"/usr/bin","/bin",NULL};
char * mot_[] ={"ls","|","cat","|","wc",NULL};

void fairePlusiersPipe(char ** dirs,char **mot){
  char inbuf[MaxPathLength];
  int p[2],c[2], j, pid,i;
  int nb_pipe,dernier=0;
  char pathname[MaxPathLength];
  
  for(i=0,nb_pipe=0;mot[i]!=NULL; i++)
    if(strcmp(mot[i],"|")==0)nb_pipe++;
	
  memset(inbuf,0,MaxPathLength);
   /* open pipe */

   if(pipe(p) == -1)
   {    perror("pipe call error");
        exit(1);
   }
   
   if(pipe(c) == -1)
   {    perror("pipe call error");
        exit(1);
   }
   
   pid= fork();
 for(dernier=0;dernier<nb_pipe;dernier++)
   switch(pid){
   case -1: perror("error: fork call");
            exit(2);

   case 0: 
     if(dernier==0){
         close(c[0]);
         close(p[0]);  
	 if(dup2(c[1], 1)== -1){
	    perror( "dup2 failed" );
	    _exit(1);
	 }
	 close(c[1]); 
	 if(dup2(p[1],c[0])== -1){
	    perror( "dup2 failed" );
	    _exit(1);
	 }
	 for(i = 0; dirs[i] != NULL; i++){
	 snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
	 execlp(pathname,mot[dernier*4],NULL);// 1er ls
	 }
     }if(dernier==(nb_pipe-1)){
       close(p[0]);
       close(p[1]);
       if(dup2(0,c[0])== -1){
	    perror( "dup2 failed" );
	    _exit(1);
	 }
       close(c[1]);
       if(dup2(c[1],1)== -1){
	    perror( "dup2 failed" );
	    _exit(1);
       }
       close(c[1]);
       for(i = 0; dirs[i] != NULL; i++){
       snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
       execlp(pathname,mot[dernier*4],NULL);// 3eme wc
       }
     }else 
       break;
   default:  
     if(dernier==(nb_pipe-1)){
       close(c[0]); 
       close(p[1]); 
       if(dup2(c[0],p[1])== -1){
	    perror( "dup2 failed" );
	    _exit(1);
       }
       close(p[1]);
       close(c[0]);  
       if(dup2(c[1],p[0])== -1){
	    perror( "dup2 failed" );
	    _exit(1);
       }
       for(i = 0; dirs[i] != NULL; i++){
       snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
       execlp(pathname,mot[dernier*4+2],NULL);// 2eme cat
       }
     }
   }
   exit(0);
}

int main(){
  fairePlusiersPipe(dirs_,mot);
}
