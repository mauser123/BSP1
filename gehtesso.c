/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test.c
 * Author: debian
 *
 * Created on 30. Oktober 2017, 04:45
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * 
 */
int main(int argc, char** argv) {
    pid_t pid;
    int mypipefd[2];
    int ret;
	int uhr = 0;
	char a;
    ret = pipe(mypipefd);
    char buf[20];
    if(ret == -1){
        perror("pipeerror");
        exit(1);
    }
    
    pid = fork();
    if(pid == 0){
        /*child*/
        printf("child %d, my parent is %d\n",getpid(), getppid());
		printf("Geben sie einen Befehl ein!\n";
		cin>>a;
		if(a == 'q'){
		write(mypipefd[1], "Bye!", 4);
		}
		write(mypipefd[1], a, 1);
    }
    else{
        /*parent*/
        printf("Parent %d, my child is %d\n", getpid(), pid);
		
	wait(NULL);
        read(mypipefd[0],buf, 15);
        printf("buf: %s\n", buf);
		if(buf == 'q'{
		return 0;}
    }
    
    
    
    
    
    return 0;
}
