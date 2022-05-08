#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/msg.h>


void randomString(int n, const char seed[], char *buf);

void ToCapitalString(char *buf, int n);

int main() {
    pid_t c1;
    int  n;
    char seed_string[29] = "abcdefghijklmnopqrstuvwxyz ";
    strcat(seed_string, "\n");

    c1 = fork(); //forking process
    if (c1 == -1) {
        fprintf(stderr, "Fork failure c1\n");
        exit(EXIT_FAILURE);
    }
    if (c1 == 0) { //Child code P2
        key_t  key;
        int msgid;

        key = ftok("progfile.txt",65); //shared key
        if(key == -1){
            perror("key error");
            exit(-1);
        }
        msgid = msgget(key,0666 | IPC_CREAT); //open / create queue
        if(msgid == -1){
            perror("msgid error");
            exit(-1);
        }
        int size;
        srand(time(NULL) + getppid()); //seed for rand()
        while (1) {
            char *in_buf, *out_buf;
            msgrcv(msgid,&size,sizeof(int),0,0);
            //read(fd_c, &size, sizeof(size));
            in_buf = malloc((size + 1) * sizeof(char));
            msgrcv(msgid,in_buf,size,0,0);
            //read(fd_c, in_buf, size);
            printf("Received string from P1:\t %s\t SIZE:%lu\n", in_buf, strlen(in_buf));
            ToCapitalString(in_buf, size);
            printf("Converted to Capital...:\t %s\n", in_buf);

            sleep(2);
            n = rand() % 100;
            if (n == 0) {
                printf("CHILD generated 0 size string.. Dying\n");
                msgctl(msgid,IPC_RMID,NULL); //reve the queue from the system
                exit(EXIT_SUCCESS);
            }
            out_buf = malloc((n + 1) * sizeof(char));
            randomString(n, seed_string, out_buf);
            msgsnd(msgid,&n,sizeof(int),IPC_NOWAIT);
            msgsnd(msgid,out_buf,strlen(out_buf),IPC_NOWAIT);

            free(in_buf);
            free(out_buf);

        }

    } else { //Parent code P1
        key_t  key;
        int msgid;

        key = ftok("progfile.txt",65); //shared key
        if(key == -1){
            perror("key error");
            exit(-1);
        }
        msgid = msgget(key,0666 | IPC_CREAT); //open / create queue
        if(msgid == -1){
            perror("msgid error");
            exit(-1);
        }
        int size;
        srand(time(NULL)); //seed for rand()
        while (1) {

            char *in_buf, *out_buf;
            sleep(1);
            n = rand() % 100;
            if (n == 0) {
                kill(c1, SIGKILL);
                c1 = wait(NULL);
                if (c1 == -1)
                    perror("error on wait");
                else {
                    printf("Child %d killed\n", c1);
                    msgctl(msgid,IPC_RMID,NULL);
                    exit(EXIT_SUCCESS);
                }
            }
            out_buf = malloc((n + 1) * sizeof(char));
            randomString(n, seed_string, out_buf);
            msgsnd(msgid,&n,sizeof(int),IPC_NOWAIT);
            msgsnd(msgid,out_buf,strlen(out_buf),IPC_NOWAIT);

            msgrcv(msgid,&size,sizeof(int),1,0);
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
            in_buf = malloc((size + 1) * sizeof(char));
            msgrcv(msgid,&in_buf,size,1,0);
            printf("Received string from P2 (child):\t %s\t SIZE:%lu\n", in_buf, strlen(in_buf));
            ToCapitalString(in_buf, size);
            printf("Converted to Capital...:\t %s\n", in_buf);
            free(in_buf);
            free(out_buf);
        }
    }
    return 0;
}

void randomString(int n, const char seed[], char *buf) {
    int c;
    for (int i = 0; i < n; i++) {
        c = rand() % 29;
        buf[i] = seed[c];
    }
}

void ToCapitalString(char *buf, int n) {
    for (int i = 0; i < n; i++) {
        buf[i] = toupper((unsigned char) buf[i]);
    }
}