#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <math.h>

struct info{
	int count;
	int pow;
};

void *tF(void *par){
	int rc;
	void *status;
	pthread_t th[2];
	struct info *limit;
	limit = (struct info *) par;
	
	if(limit->count >= limit->pow){
	//printf("%ld ",pthread_self());
	pthread_exit(NULL);
	}
	
	for (int i=0; i<2; i++) {
		limit->count++;
		printf("%ld ",pthread_self());
		rc = pthread_create(&th[i],NULL,tF,(void*) &limit);
	}
	for (int i=0; i<2; i++) {
		//printf("\n");
  		rc = pthread_join(th[i],&status);
  	}
	
	
	
	pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
  int n = atoi(argv[1]);
  pthread_t th[n];
  
  int rc;
  void *status;
  struct info limit;
  limit.pow = limit.count = 0;
  
  limit.pow  = 16;
  
  for (int i=0; i<2; i++) {
  limit.count++;
  printf("%ld\t ",pthread_self());
  rc = pthread_create(&th[i],NULL,tF,(void *) &limit);
  }
  
  for (int i=0; i<2; i++) {
  //printf("\n");
  rc = pthread_join(th[i],&status);
  }
  pthread_exit(NULL);

  return (1);
}
