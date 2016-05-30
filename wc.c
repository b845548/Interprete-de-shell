#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#define MAX_SIZE 1024




int main(int args,char ** argv){
	int line_count=0;
	int character_count=0;
	int word_count=0;
	long filesize;
	char * buffer,*ptr;
	char buf[MAX_SIZE];
	FILE * F;
	F= fopen(argv[1],"r");
	if(F==NULL)fprintf(stdout,"Not found file\n");
	else{
		while(fgets(buf,MAX_SIZE,F)!=NULL)
		line_count++;	
		rewind(F);
		while(fgetc(F)!=EOF)character_count++;
		rewind(F);
		fseek(F,0,SEEK_END);
		filesize=ftell(F);
		rewind(F);
		buffer=(char *)malloc(filesize*sizeof(char));
		memset(buffer,0,filesize);
		fread(buffer,1,filesize,F);
		ptr=strtok(buffer," \n");
		while(ptr!=NULL){
		word_count++;
		ptr=strtok(NULL," \n");
		}		
		if(argv[2]==NULL)
			fprintf(stdout,"\t%d\t%d\t%d\t%s\n",line_count,word_count,filesize,argv[1]);
		else if(strcmp(argv[2],"-l")==0)
			fprintf(stdout,"\t%d\t%s\n",line_count,argv[1]);		
		else if(strcmp(argv[2],"-w")==0)
			fprintf(stdout,"\t%d\t%s\n",word_count,argv[1]);
		else if(strcmp(argv[2],"-c")==0)
			fprintf(stdout,"\t%d\t%s\n",filesize,argv[1]);
		else if(strcmp(argv[2],"-m")==0)
			fprintf(stdout,"\t%d\t%s\n",character_count,argv[1]);
	fclose(F);
	}

	}
}
