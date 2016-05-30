#include<stdio.h>
#include<unistd.h>
#include<assert.h>
#include<sys/wait.h>

enum{
  Nfois = 100 * 1000,
};

int main(){
  int i, t, etat, newpid;

  for(i = 0; i <Nfois; i++){
    newpid = fork();
    if(newpid == 0){
      //enfant : ne rien faire
      printf("commence\n");
      return 0;
    }
    //parent
    assert(newpid > 0);
    t = wait(&etat);
    assert(t == newpid);
  }
  return 0;
}
