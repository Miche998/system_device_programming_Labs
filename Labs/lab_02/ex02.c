#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

typedef struct {
  int id;
  long r_no;
  char surname[30];
  char name[30];
  int mark;
 } mys;
 
int main(int argc, char* argv[]){

 char input;
 int n;
 mys data;
 
 int fp;
 int nR;
 int nbytes;
 int menu = 1;
 while(menu){
 	
 	printf("Insert command and position:\n");
  	scanf("%c %d",&input,&n);
  	if(input == 'E'){
  		menu=0;
  		break;
  	}
  	if(input == 'R'){
  		printf("Reading input data...\n");
  	 	fp = open("file_2.txt",O_RDONLY);
	 	lseek(fp,(n-1)*sizeof(data),SEEK_SET);
	 	nR = read (fp, &data, sizeof(data));
	 	fprintf(stdout,"%d %ld %s %s %d\n",data.id, data.r_no, data.surname, data.name, data.mark);
	 	close(fp);
	 	sleep(1);
  	}if(input == 'W'){
  	 	fp = open("file_2.txt",O_WRONLY);
	 	printf("Insert student data fields:\n");
		printf("id (int) r_no (long) surname (String) name (String) mark (int)\n");
		scanf("%d %ld %s %s %d",&data.id,&data.r_no,data.surname,data.name,&data.mark);
		lseek(fp,(n-1)*sizeof(data),SEEK_SET);
		if((n-1)*sizeof(data) >= SEEK_END){
			printf("Over-write new record on file in position %d\n",n);
		}else{
			printf("Over-write student's record %d\n",n);
		}
		nbytes =  write(fp,&data,sizeof(data));
	 	fprintf(stdout,"%d %ld %s %s %d\n",data.id, data.r_no, data.surname, data.name, data.mark);
	 	close(fp);
	 	sleep(1);
  	}
 }
 
 return (1);
}
