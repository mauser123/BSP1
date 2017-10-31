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

	if( ret == -1){
	perror("pipe"); exit(EXIT_FAILURE);	
}
while(true){
	cpid = fork();
	
	if(cpid == -1){perror("fork"); exit(EXIT_FAILURE);
}
	if(cpid == 0){ /*child reads from pipe*/
	//close(mypipe[1]); /* schliesst unbenutztes write ende*/
	
	printf("Child %d, my parent is %d \n",getpid(), getppid());
	read(mypipe[0], buf,4);
		
        printf("buf: %s \n", buf);
		
	_exit(EXIT_SUCCESS);
}
	else{ /* PArent*/
	printf("Parent %d, my child is %d \n",getpid(), cpid);
	std::cin>> input;
	/*if(input[0] == 'x'){
	printf("BYE!\n");
	exit(1);}
	else*/
	write(mypipe[1],&input, 4);
	
	
	wait(NULL);
	exit(EXIT_SUCCESS);

}
}	



    return 0;
}

