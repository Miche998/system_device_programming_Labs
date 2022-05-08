#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

float random_float();
void print_vector(int n,float *v);
void initialize_vector(float *f,int n);
void allocateMatrix(float ***m,int r,int c);
void initialize_matrix(int n, float **m);
void print_matrix(int n,float **m);
void *tF(void *args);
pthread_barrier_t bar;

typedef struct{
    float v;
    float *v2;
    float *out;
    float **mat;
    int id;
    int n_t;
    float r;
}threads_t;

int main() {
    srand(time(NULL));
    int n = 2,i,j;
    pthread_t tid[n];
    threads_t *t;
    float res = 0.0;
    float v1[n],v2[n],**m,out_v[n];
    t = malloc(n*sizeof(threads_t));
    initialize_vector(v1,n); initialize_vector(v2,n);
    allocateMatrix(&m,n,n);
    initialize_matrix(n, m);
    print_vector(n,v1);print_vector(n,v2);
    print_matrix(n,m);

    pthread_barrier_init(&bar,NULL,n);
    for(i = 0; i < n; i++){
        t[i].v = v1[i];
        t[i].mat = m;
        t[i].out = out_v;
        t[i].id = i;
        t[i].n_t=n;
        if(i == n-1){
            t[i].v2 = v2;
        }
        pthread_create(&tid[i],NULL,tF,(void*)&t[i]);
    }
    for(i=0;i<n;i++)
        pthread_join(tid[i],NULL);



    print_vector(n,out_v);
    printf("\nRES = %f",t[n-1].r);
    return 0;
}

float random_float(){
        float x = rand();
        x =  x/((float)RAND_MAX+1);
        return (float)((1.0 * x) - 0.5);
}
void initialize_vector(float *f,int n){
    for( int i = 0 ; i < n; i++){
        f[i] = random_float();
    }
}
void allocateMatrix(float ***m,int r,int c)
{
    *m = malloc(r*sizeof(int*));
    for (int i = 0; i < r; i++)
        (*m)[i] = malloc(c*sizeof(int));
}


void initialize_matrix(int n, float **m){
    for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j < n; j++) {
            m[i][j] = random_float();
        }
    }
}
void print_vector(int n,float *v){
    int i;
    printf("\t\t\t\t\t------------------ Vector is printing... --------------------\n");
    for ( i = 0; i < n; i++){
        printf("%f ",v[i]);
    }
    printf("\n");
}

void print_matrix(int n,float **m){
    int i,j;
    printf("\t\t\t\t\t------------------ Matrix is printing... --------------------\n");
    for ( i = 0; i < n; i++){
        for ( j = 0; j < n; j++){
            printf("%f ",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void *tF(void *args){
    int j;
    int i = ((threads_t *)args)->id;
    for(j = 0; j < ((threads_t *)args)->n_t; j++){
        ((threads_t *)args)->out[i]+=((threads_t *)args)->v*((threads_t *)args)->mat[j][i];
    }
    pthread_barrier_wait(&bar); // wait for synch in order to have correctsult in out (vector)
    if(((threads_t *)args)->id != ((threads_t *)args)->n_t-1) //if i'm not the last thread i quit
        pthread_exit(NULL);
    else{ //force the last thread to process the final result
        ((threads_t *)args)->r=0;
        for(i = 0; i < ((threads_t *)args)->n_t; i++){
            ((threads_t *)args)->r += ((threads_t *)args)->out[i]*((threads_t *)args)->v2[i];
        }
        pthread_exit(NULL);
    }
}
