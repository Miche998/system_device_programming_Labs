#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

void mat_mul (int **A, int **B,int r, int x,int c, int ***C);
void allocateMatrix(int ***m,int r,int c);
void freeMatrix(int ***m,int r);

int count = 0;
struct m{
	int **C;
	int a_ik;
	int b_kj;
	int i;
	int j;
	int k;
};

void *tF(void *par){
	count ++;
	
	struct m *data;
	data = (struct m *) par;
	data->C[data->i][data->j] += data->a_ik * data->b_kj;
	pthread_exit(NULL);
}

int main (int argc, char* argv[]) {

  int **A;
  int **B;
  allocateMatrix(&A,2,3);
  allocateMatrix(&B,3,2);
  int **C;
  
  for(int i =0;i<2;i++){
  	for(int j=0;j<3;j++){
  		printf("A[%d][%d]\n",i,j);
  		scanf("%d",&A[i][j]);
  		printf("B[%d][%d]\n",j,i);
  		scanf("%d",&B[j][i]);
  	}
  }
  mat_mul(A,B,2,3,2,&C);
  
  freeMatrix(&A,2);
  freeMatrix(&B,3);
  
  pthread_exit(NULL);	
  return (1);
}

void mat_mul (int **A, int **B,int r, int x,int c, int ***C){
 
 
 int rc;
 void *status;
 struct m data;
 allocateMatrix(C,r,c);
 allocateMatrix(&data.C,r,c);

 pthread_t tid;
 
 for(data.i =0;data.i<r;data.i++){
 	data.k =0;
  	for(data.j=0;data.j<c;data.j++){
  		
  		printf("data->i %d data->j %d\n", data.i,data.j);
  		for(int p = 0; p <x; p++){
  			if(data.k>=x)
  				data.k=0;
  			data.a_ik = A[data.i][data.k];
  			data.b_kj = B[data.k][data.j];
  		
  			rc = pthread_create(&tid,NULL,tF,(void *) &data);
  			rc = pthread_join(tid,&status);
  			data.k++;
  		}
  	}
  }
  for(int i =0;i<r;i++){
  	for(int j=0;j<c;j++){
  		printf("%d ",data.C[i][j]);
  	}
	printf("\n");
  }
  freeMatrix(C,r);
  freeMatrix(&data.C,r);
  
}

void allocateMatrix(int ***m,int r,int c)
{
    *m = malloc(r*sizeof(int*));
    for (int i = 0; i < r; i++)
        (*m)[i] = malloc(c*sizeof(int));
}

void freeMatrix(int ***m,int r)
{
    for (int i = 0; i < r; i++)
        free((*m)[i]);
    free(*m);
    *m = 0;
}
