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
#include <signal.h>


/*
 * 
 */
void myhandle(int mysignal){
 printf("myhandle with signal %d\n", mysignal);

}
int main(int argc, char** argv) {
    int i = 0;
    signal(SIGTERM, myhandle);
	while(1){
	printf("i = %d\n", i);
	i++;
	sleep(1);}
    return 0;
}

