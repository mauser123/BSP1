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
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
	int mypipe[2];
	int ret;
	pid_t cpid;
	char buf[20];
	ret = pipe(mypipe);
	char input[5];
	int time = 0;
	int mode = 0;

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
	if(buf[0] == 'm'){
	mode++;
	printf("Test mode ausgabe\n");
	}		
	if(buf[0] == 's'){
	time++;
	printf("Zeit: %i\n", time);}
	if(buf[0] == 'q'){
	printf("Bye!\n");
	exit(0);
	//AVGruntime wie auch immer
	}
	else
	printf("buf: %s \n", buf);
	
	while(mode %2 == 1){
	sleep(1);
	time++;
	printf("Zeit: %i\n", time);
	if(buf[0] == 'q'){
	printf("Bye!\n");
	exit(0);
	}
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

