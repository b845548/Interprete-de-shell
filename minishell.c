/*
  Projet de minishell
  
  JEMOUI Nader N'14507159
  BAE Hobean N'14507159

  Liste de fichiers:
  minishell.c 
  decouper.c
  wc.c
  cat.c
  plusiersPipe.c

 */

# include "decouper.c"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <assert.h>
# define PROMPT "? "

enum {
  ERR= -1,
  ENFANT= 0,
  MaxLigne = 1024,              // longueur max d'une ligne de commandes
  MaxMot = MaxLigne / 2,        // nbre max de mot dans la ligne
  MaxDirs = 100,		// nbre max de repertoire dans PATH
  MaxPathLength = 512,		// longueur max d'un nom de fichier
};
void fairePipe(char ** dirs,char ** mot){
  int i;
  char pathname[MaxPathLength];
    int pipefd[2];
    if (pipe(pipefd)) {
	perror("pipe");
	exit(1);
    }
    switch (fork()) {
    case ERR:
        perror("fork");
        exit(1);
    case ENFANT:
        close(pipefd[0]);  
        dup2(pipefd[1], 1);
        close(pipefd[1]);  
	for(i = 0; dirs[i] != NULL; i++){
	snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
	if(strcmp(mot[1],"|")==0)
      	execl(pathname, mot[0], (char *)NULL);
	else 
    	execl(pathname, mot[0],mot[1],(char *)NULL);
	}
        exit(1);
    default: /* parent */
        close(pipefd[1]);  
        dup2(pipefd[0], 0);
        close(pipefd[0]); 
 	for(i = 0; dirs[i] != NULL; i++){
      	snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[2]);
        if(strcmp(mot[1],"|")==0)
   	execl(pathname, mot[2], (char *)NULL);
  	else
  	execl(pathname, mot[3], (char *)NULL);
  	}
        exit(1);
    }
}

int main(int argc, char * argv[]){
  char ligne[MaxLigne];
  char pathname[MaxPathLength];
  char * mot[MaxMot];
  char * dirs[MaxDirs];
  int i, tmp, count_pipe;

  /* Decouper UNE COPIE de PATH en repertoires */
  decouper(strdup(getenv("PATH")), ":", dirs, MaxDirs);	
	system("clear");
	printf("\n\tSystem d'exploitation\n");
	printf("\tProjet : minishell\n");
	printf("\t\t\t\tJEMOUI Nader N'14507159\n");
	printf("\t\t\t\tBAE Hobean N'14500464\n\n");
/* Lire et traiter chaque ligne de commande */
  for(printf(PROMPT); fgets(ligne, sizeof ligne, stdin) != NULL; printf(PROMPT)){
    decouper(ligne, " \t\n", mot, MaxMot);
    if (mot[0] == NULL)            // ligne vide
      continue;

    switch(tmp = fork()){               // lancer le processus enfant
    case ERR:
    	perror("fork");
    	continue;
    case ENFANT: // enfant : exec du programme
	
	if(strcmp(mot[0],"cd")==0){
	if(mot[1]==NULL)
	chdir(strdup(getenv("HOME")));	
	else 
	chdir(mot[1]);	
	break;
	} 
	for(i=0 ; dirs[i] != NULL; i++);
		dirs[i]=getcwd(NULL,0);
   	for(i=0,count_pipe=0; mot[i]; i++)
		if(strcmp(mot[i],"|")==0)count_pipe++;
  	/////////// execution ///////////
   	if(count_pipe==1)
		fairePipe(dirs,mot); 
	else 
   	for(i = 0; dirs[i] != NULL; i++){
      	snprintf(pathname, sizeof pathname, "%s/%s", dirs[i], mot[0]);
      	execv(pathname, mot);
   	}
  	// aucun exec n'a fonctionne
	fprintf(stderr, "%s: not found\n", mot[0]);
   	exit(1);
   default : 
   	if (tmp != 0){   // parent : attendre la fin de l'enfant
   	while(wait(NULL) != tmp);
   	continue;
   	}
     }
  }
  printf("Bye\n");
  return 0;
}
