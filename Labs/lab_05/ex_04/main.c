#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    int *v;
    char *filename;
    int size;
    int id;
}args_t;


int count=0;
int curr_thread=-1;
sem_t sem,me;
int n_threads;
void *adder(void * arg);
void quicksort(int *number,int first,int last);
void merge(int a[],int i1,int j1,int i2,int j2);
void mergesort(int a[],int i,int j);

int main(int argc, char *argv[]) {
    int i, size = 0;
    pthread_t *tids;
    args_t *args;

    if (argc != 7)
        exit(1);
    n_threads = argc-1;

    tids = malloc(n_threads*sizeof(pthread_t));
    args = malloc(n_threads*sizeof(args_t));

    //pthread_barrier_init(&bar,NULL,n_threads-1);
    sem_init(&sem,0,0);
    sem_init(&me,0,1);
    for( i = 0 ; i < n_threads-1 ; i++){
        args[i].id = i;
        args[i].filename= strdup(argv[i+1]);
        pthread_create(&tids[i],NULL,adder,(void *)&args[i]);
    }

    int *final = malloc(size*sizeof(int));
    int previous_size = 0;

    while(count != n_threads-1 ) {
        sem_wait(&sem);
        previous_size = size;
        size+=args[curr_thread].size;
        final = realloc(final,size*sizeof(int));
        memcpy(final + previous_size, args[curr_thread].v, args[curr_thread].size * sizeof(int));

        mergesort(final, 0, size - 1);
        for (i = 0; i < size; i++)
            printf("%d ", final[i]);
        printf("\n COUNT = %d & curr_T=%d\n",count,curr_thread);
    }
    for(i = 0; i < n_threads; i++) {
        pthread_join(tids[i], NULL);
    }
    /* WRITE TO FILE */
    int *final2 = malloc(size*sizeof(int));
    FILE *fp;
    fp = fopen(argv[argc-1],"w");
    if ( fp == NULL)
        perror("ERROR INTO OPENING FILE");
    fwrite(&size, 4, 1, fp);
    fwrite(final,sizeof(final[0]),size,fp);
    fclose(fp);

    /* FOR DEBUG REASON I CHECK IF I WROTE CORRECTLY ON BINARY FILE */
    fp = fopen(argv[argc-1],"r");
    if ( fp == NULL)
        perror("ERROR INTO OPENING FILE");
    fread(final2,sizeof(final[0]),size+1,fp);
    printf("\n--------------------- CONTENT OF FILE %s ---------------------\n",argv[argc-1]);
    for( i = 0; i < size+1; i++)
        printf("%d ",final2[i]);
    return 0;
}

void *adder(void * arg){
    FILE *fp;
    int i = 0;
    fp = fopen(((args_t*)arg)->filename,"r");
    if ( fp == NULL)
        perror("ERROR INTO OPENING FILE");
    char buffer[256];
    fscanf(fp,"%s %d: %d",buffer,&((args_t*)arg)->size,&((args_t*)arg)->size);
    ((args_t*)arg)->v = malloc(((args_t*)arg)->size*sizeof(int));
    while(fscanf(fp," %d",&((args_t*)arg)->v[i])!=EOF){
        i++;
    }
    quicksort(((args_t*)arg)->v,0,(((args_t*)arg)->size)-1);
    fclose(fp);

    sem_wait(&me); // 1 thread at time in CS
    curr_thread=((args_t*)arg)->id; // copy the current thread_id to curr-threa global variable
    count++;
    sem_post(&sem); //wake up main thread
    sem_post(&me); // exit CS
    pthread_exit(NULL);
}

void quicksort(int *number,int first,int last){

    int i, j, pivot, temp;

    if(first<last){

        pivot=first;

        i=first;

        j=last;

        while(i<j){

            while(number[i]<=number[pivot]&&i<last)

                i++;

            while(number[j]>number[pivot])

                j--;

            if(i<j){

                temp=number[i];

                number[i]=number[j];

                number[j]=temp;

            }

        }

        temp=number[pivot];

        number[pivot]=number[j];

        number[j]=temp;

        quicksort(number,first,j-1);

        quicksort(number,j+1,last);

    }

}

void mergesort(int a[],int i,int j)
{
    int mid;
    if(i<j)
    {
        mid=(i+j)/2;
        mergesort(a,i,mid); //left recursion
        mergesort(a,mid+1,j); //right recursion
        merge(a,i,mid,mid+1,j); //merging of two sorted sub-arrays
    }
}

void merge(int a[],int i1,int j1,int i2,int j2)
{
    int temp[50]; //array used for merging
    int i,j,k;
    i=i1; //beginning of the first list
    j=i2; //beginning of the second list
    k=0;
    while(i<=j1 && j<=j2) //while elements in both lists
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    while(i<=j1) //copy remaining elements of the first list
        temp[k++]=a[i++];
    while(j<=j2) //copy remaining elements of the second list
        temp[k++]=a[j++];
//Transfer elements from temp[] back to a[]
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}