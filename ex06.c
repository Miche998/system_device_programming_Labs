#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int flag1 = 0;
int flag2 = 0;


void manager (int sig){
 if(sig==SIGUSR1){
 	if(flag2>0){
 		printf("SUCCES\n");
 	}
 	
 	flag1++;
 	
 	if(flag1==2)
 		printf("ERROR\n");
 	if(flag1==3)
 		exit(-1);
 		
 	flag2=0;
 }
 else if(sig==SIGUSR2){
 
 	if(flag1>0){
 		printf("SUCCES\n");
 	}
 	
 	flag2++;
 	
 	if(flag2==2)
 		printf("ERROR\n");
 	if(flag2==3)
 		exit(-1);
 	flag1=0;
 }
 return;
}

int main(){
 signal(SIGUSR1, manager);
 signal(SIGUSR2,manager);
 
 while(1);
 return 1;
}
