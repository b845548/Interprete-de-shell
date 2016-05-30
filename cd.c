#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <unistd.h>
int main(int args, char ** argv){
int MAX_SIZE=1024;
 if(args==1){
   chdir("/");
   system("PWD='/'");   
 }
 else if(args==2 && strcmp(argv[1],".")==0);
 else if(args==2 && strcmp(argv[1],"..")==0){
        int i;	
	char nv[MAX_SIZE];
	char buff[MAX_SIZE];
	memset(nv,0,(size_t)MAX_SIZE);
	memset(buff,0,(size_t)MAX_SIZE);
	strcpy(buff,getcwd(NULL,0));
	for(i=(strlen(getcwd(NULL,0))-1); isalpha(buff[i]) || isdigit(buff[i]);--i){			buff[i]=0;
			}	
	buff[i]=0;
	chdir(buff);
	strcpy(nv,"PWD='");
	strcat(nv,buff);
	strcat(nv,"'");
	system(nv);
	system("echo $PWD");
  }else if(args==2){
	char nv[MAX_SIZE];
	memset(nv,0,(size_t)MAX_SIZE);
        chdir(argv[1]);
	strcpy(nv,"PWD='");
	strcat(nv,getcwd(NULL,0));
	strcat(nv,"'");
	system(nv);
	system("echo $PWD");
  }
  return 0;
}
