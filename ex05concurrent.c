#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void binary (int *vet,int n,int i);

int main (int argc,char *argv[]) {
  int n;
  int *vet;

  n = atoi (argv[1]);

  vet = (int *)malloc(n * sizeof(int));
  if (vet == NULL) {
    printf("Allocatin Error.\n");
    exit(1);
  }

  printf("Binary Numbers:\n");
  binary(vet, n, 0);
  free(vet);

  return 0;
}

void binary (int *vet,int n,int i) {
  int j;
  pid_t pid;
  
  for (int k=0; k<n; k++) {
   pid=fork();
    if (pid){
    	vet[k]=1;
    }
    else{
    	vet[k]=0;
    }
    if(k==n-1){
    for (j=0; j<n; j++) {
   	 printf("%d", vet[j]);
  	}
  	printf("\n");
    }
  }
  
 
  return;
}
