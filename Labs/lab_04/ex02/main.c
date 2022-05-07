#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    int *v;
    char *filename;
    int size;
}args_t;

pthread_barrier_t bar;
int n_threads;
void *adder(void * arg);
void quicksort(int *number,int first,int last);
void merge(int a[],int i1,int j1,int i2,int j2);
void mergesort(int a[],int i,int j);

 int main(int argc, char *argv[]) {
    int i, size = 0;
    pthread_t *tids;
    args_t *args;

    if (argc != 5)
        exit(1);
    n_threads = argc-1;

    tids = malloc(n_threads*sizeof(pthread_t));
    args = malloc(n_threads*sizeof(args_t));

    pthread_barrier_init(&bar,NULL,n_threads-1);
    for( i = 0 ; i < n_threads-1 ; i++){
        args[i].filename= strdup(argv[i+1]);
        pthread_create(&tids[i],NULL,adder,(void *)&args[i]);
    }

    for(i = 0; i < n_threads; i++) {
        pthread_join(tids[i], NULL);
    }
    for( i = 0 ; i < n_threads-1 ; i++)
        size+= args[i].size;
    int *final = malloc(size*sizeof(int));
     int *final2 = malloc(size*sizeof(int));
    int previous_size = 0;
    for(i = 0; i < n_threads-1; i++) {
        if(i>0)
            previous_size += args[i-1].size;
        memcpy(final+previous_size, args[i].v, args[i].size * sizeof(int));

    }
     mergesort(final,0,size-1);
     for( i = 0; i < size; i++)
         printf("%d ",final[i]);
    FILE *fp;
    fp = fopen(argv[argc-1],"w");
     if ( fp == NULL)
         perror("ERROR INTO OPENING FILE");
     fwrite(&size, 4, 1, fp);
     fwrite(final,sizeof(final[0]),size,fp);
     fclose(fp);
     fp = fopen(argv[argc-1],"r");
     if ( fp == NULL)
         perror("ERROR INTO OPENING FILE");
     fread(final2,sizeof(final[0]),size,fp);
     printf("\n");
     for( i = 0; i < size; i++)
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
    for(i = 0 ; i < ((args_t*)arg)->size ; i++ )
        printf("%d ",((args_t*)arg)->v[i]);
    printf("\n");
    pthread_barrier_wait(&bar);
    fclose(fp);
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