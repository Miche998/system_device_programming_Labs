#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float random_float();
void print_vector(int n,float *v);
void initialize_vector(float *f,int n);
void allocateMatrix(float ***m,int r,int c);
void initialize_matrix(int n, float **m);
void print_matrix(int n,float **m);
int main() {
    srand(time(NULL));
    int n = 3,i,j;
    float res = 0.0;
    float v1[n],v2[n],**m,out_v[n];
    initialize_vector(v1,n); initialize_vector(v2,n);
    allocateMatrix(&m,n,n);
    initialize_matrix(n, m);
    print_vector(n,v1);print_vector(n,v2);
    print_matrix(n,m);

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            out_v[i]+=(v1[j]*m[j][i]);
        }
    }
    for(i = 0; i < n; i++){
            res+=out_v[i]*v2[i];
    }

    print_vector(n,out_v);
    printf("\nRES = %f",res);
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
