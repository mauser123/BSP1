/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newmain.cpp
 * Author: debian
 *
 * Created on 31. Oktober 2017, 05:26
 */

#include <cstdlib>
#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <sys/times.h>
#define SIZE 256
int mode = 0;
/*
 * 
 */								
void myhandle(int mysignal){			//get ID ps -aux | grep "filename" ( 2 terminal notwending)
printf("myhandle with signal d%\n", mysignal); //kill -15 ID
mode++;
}
void myhandlequit(int myquitsignal){	     //kill -3 ID   //kill -9 ID terminiert ohne meldung
printf("Bye!\n", myquitsignal);
exit(0);
}

int main(int argc, char** argv) {
	int mypipe[2];
	int ret;
	pid_t cpid;
	pid_t dpid;	
	char buf[20];
	ret = pipe(mypipe);
	char input[5];
	int steps = 0;
	char buffer[SIZE];
	time_t curtime;
	struct tm *loctime;
	curtime = time(NULL);
	loctime = localtime(&curtime);
	//int mode = 0;
	signal(SIGQUIT, myhandlequit);
	signal(SIGTERM, myhandle);
	if( ret == -1){
	perror("pipe"); exit(EXIT_FAILURE);	
}
	while(true){
	cpid = fork();
	
	if(cpid == -1){perror("fork"); exit(EXIT_FAILURE);
}
	if(cpid == 0){ /*child reads from pipe*/
	
	printf("Child %d, my parent is %d \n",getpid(), getppid());
	read(mypipe[0], buf,4);
	if(buf[0] == 'p'){
	dpid = fork();
	if(dpid == -1){perror("fork"); exit(EXIT_FAILURE);}		  //ps -aux | grep "filename"
	if(dpid == 0){ //child
	printf("ZWEI Child %d, my parent is %d \n",getpid(), getppid());  //Ka ob es so ansatzweise stimmt bzw notwendig ist?
	//printf("\nEs wurden %i sekunden gezaehlt!\n",steos);		//output Zähler (glaub ich nicht gefragt?)		
	//printf("Es sind: %d sekunden vergangen seit 01.01.1970!\n",(int)time(NULL));
	fputs(asctime(loctime),stdout);  //simpel
	strftime (buffer, SIZE, "Today is %A, %B %d. \n", loctime);		//schöner aber wildes copypaste
	fputs(buffer, stdout);
	strftime (buffer, SIZE, "The time is %I:%M %p. \n", loctime);
	fputs(buffer, stdout);
	return(0);}
	else{ //parent
	printf("ZWEI Parent %d, my child is %d \n",getpid(), cpid);
	wait(NULL);
	//exit(0);
	} 
	}
        if(buf[0] == 'm'){
	mode++;
	printf("Test mode ausgabe\n");
	}		
	if((buf[0] == 's')||(buf[0]== 'S')){
	steps++;
	printf("Zeit: %i\n", steps);
	}
	if(buf[0] == 'q'){
	printf("Bye!\n");
	exit(0);
	//AVGruntime wie auch immer
	}
	else
	printf("buf: %s \n", buf);
	
	while(mode %2 == 1){
	sleep(1);
	steps++;
	printf("Zeit: %i\n", steps);
	/*if(buf[0] == 'q'){
	printf("Bye!\n");
	exit(0);
	}*/
	}
	}
	else{ /* PArent*/
	printf("Parent %d, my child is %d \n",getpid(), cpid);
	std::cin>> input;
	write(mypipe[1],&input, 4);	
	wait(NULL);
	exit(1);

	
}
}	



    return 0;
}

