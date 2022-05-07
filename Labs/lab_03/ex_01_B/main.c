#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#define STR_SIZE 50
#define WAIT_TIME_1 1
#define WAIT_TIME_2 5
#define STR_NUM 10

void randomString(int n,const char seed[],char *buf);
void ToCapitalString(char *buf,int n);
void set_fnctl(int fd, int flags);
void clr_fnctl(int fd, int flags);

int main() {
    pid_t c1,c2;
    int count = 0;
    const char seed_string[26] = "abcdefghijklmnopqrstuvwxyz";
    int file1[2],file2[2],r;
    r=0;

    if(pipe(file1)==0){ //First create the pipe 0 on success

        set_fnctl(file1[0],O_NONBLOCK); //Set file1[0] to NON-BLOCKING
        set_fnctl(file2[0],O_NONBLOCK); //Set file2[0] to NON-BLOCKING
        set_fnctl(file1[1],O_NONBLOCK); //Set file1[1] to NON-BLOCKING
        set_fnctl(file2[1],O_NONBLOCK); //Set file2[1] to NON-BLOCKING

        c1 = fork();
        if(c1 == -1){
            fprintf(stderr, "Fork failure c1");
            exit(EXIT_FAILURE);
        }
        if(c1 == 0){ //C1 code
            close(file1[0]); //close read end

            while( count != 2*STR_NUM){
                sleep(WAIT_TIME_1);
                srandom(time(NULL));
                r = (rand() % (STR_SIZE+1));
                char buf[r];
                randomString(r,seed_string,buf);
                write(file1[1],&r,sizeof(r));
                write(file1[1],buf,sizeof(buf) );
                count++;
            }
            exit(EXIT_SUCCESS);

        }else{ //Parent code
            if(pipe(file2)==0) {
                c2 = fork();
                if (c2 == -1) {
                    fprintf(stderr, "Fork failure c2");
                    exit(EXIT_FAILURE);
                }
                if (c2 == 0) { //C2 code
                    close(file2[0]); //Close read end
                    while (count != 2 * STR_NUM) {
                        sleep(WAIT_TIME_2);
                        srandom(time(NULL));
                        r = (rand() % (STR_SIZE+1));
                        char buf[r];
                        randomString(r,seed_string,buf);
                        write(file2[1], &r, sizeof(r));
                        write(file2[1], buf, sizeof(buf));
                        count++;
                    }
                    exit(EXIT_SUCCESS);
                } else { //Parent Code
                    close(file1[1]); //close write end
                    close(file2[1]); //close write end
                    int c1_size, c2_size, f_count = 0;

                    while(f_count != STR_NUM) {
                        read(file1[0], &c1_size, sizeof(r)); //get string size of c1
                        char out1[c1_size];
                        read(file1[0], out1, c1_size);
                        ToCapitalString(out1,c1_size);
                        printf("CHILD1 STRING %d OF SIZE %d: %s\n",f_count+1, c1_size, out1);
                        read(file2[0], &c2_size, sizeof(r)); //get string size of c2
                        char out2[c2_size];
                        read(file2[0], out2, c2_size);
                        ToCapitalString(out2,c2_size);
                        printf("CHILD2 STRING %d OF SIZE %d: %s\n",f_count+1, c2_size, out2);
                        f_count++;
                    }
                }
            }
        }

        clr_fnctl(file1[0],O_NONBLOCK); //Clear file2[0] from NON-BLOCKING
        clr_fnctl(file2[0],O_NONBLOCK); //Clear file2[0] from NON-BLOCKING
        clr_fnctl(file1[1],O_NONBLOCK); //Clear file2[1] from NON-BLOCKING
        clr_fnctl(file2[1],O_NONBLOCK); //Clear file2[1] from NON-BLOCKING

        exit(EXIT_SUCCESS);
    }

    return 0;
}

void randomString(int n,const char seed[],char *buf){
    int c ;
    srandom(time(NULL));
    for(int i = 0; i < n; i++){
        c = rand()%26;
        buf[i] = seed[c];
    }
}
void ToCapitalString(char *buf,int n){
    for(int i = 0; i < n; i++)
        buf[i] -= 32;
}

void set_fnctl(int fd, int flags){
    int val;
    if(( val = fcntl(fd, F_GETFL, 0)) < 0)
        exit(EXIT_FAILURE);

    val |= flags; //Set the desired flag

    if(fcntl(fd, F_SETFL, val) < 0)
        exit(EXIT_FAILURE);
}

void clr_fnctl(int fd, int flags){
    int val;
    if(( val = fcntl(fd, F_GETFL, 0)) < 0)
        exit(EXIT_FAILURE);

    val &= ~flags; //Clear the desired flag

    if(fcntl(fd, F_SETFL, val) < 0)
        exit(EXIT_FAILURE);
}