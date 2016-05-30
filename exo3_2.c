#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){

  int P,PP;
  P = fork(); // Creer <Enfant> par <Parent>

  if(P == -1){// Test erreur de <Enfant>
    printf("error");
    return 1;
  }

  if(P == 0){// <Enfant>
    PP = fork();// Creer <Petit enfant> par <Enfant>
    sleep(20);// attend 20 second
    wait(NULL);// <Enfant> attends la fin de <Petit enfant>
    return 0;
  }

  if(PP == -1){ // Test erreur de <Petit enfant>
    printf("erreur");
    return 1;
  }

  if(PP == 0){// <Petit enfant>
    sleep(10);// attendre 10 second
    return 0;
  }

  if(P > 0){ // <Parent>
    wait(NULL);// parent attends la fin de <Enfant>
  }

  return 0;
}
