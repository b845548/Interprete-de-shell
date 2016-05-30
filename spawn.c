#include<stdio.h>
#include<unistd.h>
#include<string.h>

int spwan(char * fichier, char * commande, char * argument){
  int nombre;
  char * arg;
  arg = strtok (argument," ,.-");
  while (arg != NULL){
    execl(fichier,commande,arg,(void *)0);
    arg= strtok(NULL, " ,.-");
    nombre++;
  }
  printf("le programme a été lancé avec %d arguments\n",nombre);
  return 0;
}




int main(){


}
