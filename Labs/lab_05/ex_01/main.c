#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>


void randomString(int n,const char seed[],char *buf);
void ToCapitalString(char *buf,int n);

int main() {
    pid_t c1;
    int count = 0,n;
    char seed_string[29] = "abcdefghijklmnopqrstuvwxyz ";
    strcat(seed_string,"\n");
    int file1[2],file2[2];
    if(pipe(file1)==0 && pipe(file2)==0){ //First create the 2 pipes -- 0 on success
        c1 = fork();
        if(c1 == -1){
            fprintf(stderr, "Fork failure c1\n");
            exit(EXIT_FAILURE);
        }
        if(c1 == 0){ //Child code P2
            close(file1[1]); //close write end
            close(file2[0]); //close read end
            int size;
            //srand(time(NULL));
            srand(time(NULL)+getppid());
            while(1) {
                char *in_buf,*out_buf;

                read(file1[0], &size, sizeof(size));
                in_buf = malloc((size+1)*sizeof(char));
                read(file1[0],in_buf,size);
                printf("Received string from P1:\t %s\t SIZE:%lu\n",in_buf,strlen(in_buf));
                ToCapitalString(in_buf,size);
                printf("Converted to Capital...:\t %s\n",in_buf);
                sleep(2);
                n = rand()%100;
                if(n == 0) {
                    printf("CHILD generated 0 size string.. Dying\n");
                    exit(EXIT_SUCCESS);
                }
                out_buf = malloc((n+1)*sizeof(char));
                randomString(n, seed_string, out_buf);
                write(file2[1], &n, sizeof(int));
                write(file2[1], out_buf, strlen(out_buf));
                free(in_buf);
                free(out_buf);
                count++;
            }
            exit(EXIT_SUCCESS);

        }else{ //Parent code P1
            close(file1[0]); //close read end
            close(file2[1]); //close write end
            int size;
            //srand(time(NULL));
            srand(time(NULL));
            while(1) {
                char *in_buf,*out_buf;
                sleep(1);
                n = rand()%100;
                if (n == 0) {
                    kill(c1, SIGKILL);
                    c1 = wait(NULL);
                    if (c1 == -1)
                        perror("error on wait");
                    else {
                        printf("Child %d killed\n", c1);
                        exit(EXIT_SUCCESS);
                    }
                }
                out_buf = malloc((n+1)*sizeof(char));
                randomString(n, seed_string, out_buf);
                write(file1[1], &n, sizeof(int));
                write(file1[1], out_buf, strlen(out_buf));
                read(file2[0], &size, sizeof(size));
                if (size == 0) {
                    kill(c1, SIGKILL);
                    c1 = wait(NULL);
                    if (c1 == -1)
                        perror("error on wait");
                    else {
                        printf("Child %d killed\n", c1);
                        exit(EXIT_SUCCESS);
                    }
                }
                in_buf = malloc((size+1)*sizeof(char));
                read(file2[0],in_buf,size);
                printf("Received string from P2 (child):\t %s\t SIZE:%lu\n",in_buf,strlen(in_buf));
                ToCapitalString(in_buf,size);
                printf("Converted to Capital...:\t %s\n",in_buf);
                free(in_buf);
                free(out_buf);
           }
        }
        exit(EXIT_SUCCESS);
    }

    return 0;
}

void randomString(int n,const char seed[],char *buf){
    int c ;
    for(int i = 0; i < n; i++){
        c = rand()%29;
        buf[i] = seed[c];
    }
}
void ToCapitalString(char *buf,int n){
    for(int i = 0; i < n; i++) {
        buf[i] = toupper((unsigned char)buf[i]);
    }
}