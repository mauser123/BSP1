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
#include <signal.h>

void myhandle(int mysignal)
{
printf("Bye!\n");
exit(0);
	
}

int main(int argc, char** argv)
{
char str[80]
signal(SIGALRM, myhandle);
while(1){
alarm(5);
printf("> ");
fgets(str, 80 stdin);
printf("%s\n", str)




}

	return 0;
}

