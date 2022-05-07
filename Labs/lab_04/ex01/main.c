#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int *v_place;
    int id;
    int steps;
}args_t;

sem_t sem;
void *adder(void * arg);

pthread_barrier_t  bar;
int main() {
    int n = 4;
    int *v,i;
    pthread_t *tids;
    args_t *args;
    int power = (int)pow(2,n);
    v = malloc(power*sizeof(int));
    tids = malloc(power*sizeof(pthread_t));
    args = malloc(power*sizeof(args_t));

    srand(time(NULL));
    for ( i = 0; i < power; i++){
        v[i] = rand()%(9+1-1)+1;
        printf("%d ",v[i]);
    }
    //v[0]=2; v[1]= 4; v[2] = 6; v[3] =  1; v[4]=3; v[5]=  5; v[6] = 8; v[7]=  7;
    pthread_barrier_init(&bar,NULL,power);
    for(i = 0; i < power; i++) {
        args[i].v_place = v;
        args[i].id = i;
        args[i].steps = n;
        pthread_create(&tids[i], NULL, adder,(void *)&args[i]);
    }

    for(i = 0; i < power; i++) {
        pthread_join(tids[i], NULL);
    }

    printf("\nFinal vector\n");
    for ( i = 0; i < power; i++){
        printf("%d ",v[i]);
    }

    pthread_barrier_destroy(&bar);

    return 0;
}

void *adder(void * arg){
    int i=0;
    int id = ((args_t *) arg)->id;
    int n = ((args_t *) arg)->steps;
    int *v = ((args_t *)arg)->v_place;
    int tmp;
    while ( i < n){
        pthread_barrier_wait(&bar);
        if(id >= pow(2,i)){
            tmp = v[id] + v[id - (int)(pow(2,i))];
        }
        pthread_barrier_wait(&bar);
        if(id > i)
         v[id] = tmp;
        i++;
    }
    pthread_exit(NULL);

}