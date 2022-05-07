#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char* argv[]) {
  int h = atoi(argv[1]);
  int n = atoi(argv[2]);
  int count = 0;
  pid_t pid;

  for (int i=0; i<=h; i++) {
   pid=fork();
    if (pid){
    	if(i==h)
		printf("Parent leaf PID=%d\n",getpid());
    }
    else{
    	if(i==h){
      		count++;
      		printf ("Children leaf PID=%d\n",getpid());
      	}
    }
  }

  return (1);
}
