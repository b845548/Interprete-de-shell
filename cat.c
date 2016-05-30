#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 1024

int main(int args,char ** argv){
		FILE * F;
		char buf[MAX_SIZE];
	if(args==2){
		F=fopen(argv[1],"r");
		if(F==NULL)printf("Not found file\n");
		else{
		while(fgets(buf,(size_t)MAX_SIZE,F)!=NULL)
			printf("%s",buf);
		
		}		
	fclose(F);
	}else if(args==3 &&strcmp(argv[1],"<")==0){
		F=fopen(argv[2],"r");
		if(F==NULL)printf("Not found file\n");
		else{
		while(fgets(buf,(size_t)1024,F)!=NULL)
			printf("%s",buf);
		
		}		
	fclose(F);
	}else if(args==3 &&strcmp(argv[1],">")==0){
	F=fopen(argv[2],"w");
		char buf[MAX_SIZE];
		
	if(F==NULL)printf("Not found file\n");
	else{
		while(1){
			printf(">");
			fgets(buf,MAX_SIZE,stdin);
			if(*buf==0){
			  fclose(F);
			  return 0;
			}
			fputs(buf,F);
			memset(buf,0,MAX_SIZE);
		}
		fclose(F);
	}
	}else if(args==3 &&strcmp(argv[1],">>")==0){
	F=fopen(argv[2],"a");
		char buf[MAX_SIZE];
		
	if(F==NULL)printf("Not found file\n");
	else{
		while(1){
			printf(">");
			fgets(buf,MAX_SIZE,stdin);
			if(*buf==0){
			  fclose(F);
			  return 0;
			}
			fputs(buf,F);
			memset(buf,0,MAX_SIZE);
		}
		fclose(F);
	}
	}else if(args==4 &&strcmp(argv[2],">")==0){

	FILE * COPY;
	char buf[MAX_SIZE];
	F= fopen(argv[1],"r");
	COPY= fopen(argv[3],"w");
	if(F==NULL||COPY==NULL)printf("Not found file\n");
		else{
		while(fgets(buf,MAX_SIZE,F)!=0){
			fputs(buf,COPY);
		}
		fclose(F);
		fclose(COPY);
		}
	  
	}
}
