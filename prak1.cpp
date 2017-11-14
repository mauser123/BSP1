#include <cstdlib>
#include <sys/wait.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <list>
#include <sys/times.h>
#include <fstream>

#define SIZE 256

//Dinh-Phuong Duong - Markus Stuber

using namespace std;

bool mode = false;
int steps = 0;

class Prozess{
public:
Prozess();
Prozess(list<string> str);
list<string> anweisungen;

};
Prozess::Prozess(){

}
Prozess::Prozess(list<string>str){
 this->anweisungen = str;
}
								
void myhandle(int mysignal){
	if(mode == true){	
		alarm(1);
		steps++;
		cout << "Zeit: " << steps << endl;
	}
}


int main(int argc, char** argv) {
	int mypipe[2];
	int pipename;
	int tmpint;
	int value;
	pid_t cpid;
	list<Prozess*> execprozesse;
	list<Prozess*> blockedprozesse;
	char buf[20];
	list<string> file;
	pipename = pipe(mypipe);
	char input;						//q m s p
	string tmp;
	char buffer[SIZE];					//zur Zeitausgabe
	time_t curtime;
	struct tm *loctime;					
	curtime = time(NULL);
	loctime = localtime(&curtime);

        signal(SIGALRM, myhandle);

	
	if( pipename == -1){
		perror("pipe"); exit(EXIT_FAILURE);	
	}

	cpid = fork();
	
	if (cpid == 0) { //1.Child
		while (true) {
			read(mypipe[0], buf,4);
			if (buf[0] == 'p') {
				cpid = fork();					//Reporterprozesse
				if (cpid == -1) {
					perror("fork"); 
					exit(EXIT_FAILURE);
				}
				else if (cpid == 0) { //2.child
					
					fputs(asctime(loctime),stdout);
					strftime (buffer, SIZE, "Today is %A, %B %d. \n", loctime);
					fputs(buffer, stdout);
					strftime (buffer, SIZE, "The time is %I:%M %p. \n", loctime);
					fputs(buffer, stdout);
					cout<<"***********************************************************************"<<endl;
					cout<<"The current system state is as follows:"<<endl;
					cout<<"***********************************************************************"<<endl;
					cout<<"CURRENT TIME: "<<steps<<endl;
					cout<<"RUNNING PROCESS:"<<endl;
					cout<<"pid   pid  priority \tvalue start time\t CPU time used so far"<<endl;     
					//Code zur ausgabe des at the moment laufenden prozesses	
					cout<<"BLOCKED  PROCESSES:"<<endl;
					cout<<"pid   pid  priority\tvalue start time\t CPU time used so far"<<endl; 
					//Code zur ausgabe der blockierten prozesse
					cout<<"PROCESSES READY TO EXECUTE:" <<endl;
					cout<<"pid   pid  priority\tvalue start time\t CPU time used so far"<<endl; 
					//Code zur ausgabe der bereiten prozesse
					exit(0);
					
				} else { //2.parent
					wait(NULL);
				} 
			
			} else if (buf[0] == 'm') {			//Toggeln mit m auto mode
				if (mode == false) {
					mode = true;			
				} else { 
					mode = false;
				}
			} 	else if (buf[0] == 'u') {

				/*execprozesse.push_back(new Prozess(blockedprozesse);
				blockedprozesse.pop_front();*/
				cout<<"exec SIZE"<<execprozesse.size();
				cout<<"blocked SIZE"<<blockedprozesse.size();
				}else if (buf[0] == 's') {
				if(mode == true){
				cout <<"Nicht erlaubt!" <<endl;}
				else if(execprozesse.size() > 0){
				tmp = execprozesse.front()->anweisungen.front();
				cout<< tmp <<endl;
				execprozesse.front()->anweisungen.pop_front();
				switch(tmp[0]){
				case 'S': tmp.erase(0,2);
				tmpint = stoi(tmp);
				value = tmpint;
				cout<<"TestAusgabeValue "<< value<< endl;
				break;
				case 'A': tmp.erase(0,2);
				tmpint = stoi(tmp);
				value = value + tmpint;
				cout<<"TestAusgabeValue "<< value<< endl;
				break;
				case 'D': tmp.erase(0,2);
				tmpint = stoi(tmp);
				value = value - tmpint;
				cout<<"TestAusgabeValue "<< value<< endl;
				break;
				case 'B': /*blockedprozesse.push_back(new Prozess(execprozesse);
				execprozesse.pop_front();*/
				break; //Methode um in die Blocked liste zu schieben
				case 'E': execprozesse.pop_front();
				cout<<"SIZE"<<execprozesse.size()<<endl;
				break;//Beenden des Simulierten prozess
				case 'R': printf("Liesst neue datei ein\n");
				tmp.erase(0,2);				
				string filename;
				ifstream input(tmp);
				string buff;
				while(input.good()){
				getline(input, buff);
				file.push_back(buff);
				cout << buff <<endl; }
				
				execprozesse.push_back(new Prozess(file));
				cout<<"SIZE "<<execprozesse.size()<<endl;
				cout<<"File.Size"<< file.size()<<endl;
				file.clear();
				break;//Datei einlesen 				
				}
				steps++;
				cout << "Zeit: " << steps << endl;}
				
				else{
				steps++;
				cout << "Zeit: " << steps << endl;}
			} else if(buf[0] == 'T'){
				string filename;
				ifstream input("init.cpp");
				string buff;
				while(input.good()){
				getline(input, buff);
				file.push_back(buff);
				cout << buff <<endl; }
				execprozesse.push_back(new Prozess(file));
				cout<<"SIZE"<<execprozesse.size()<<endl;
				file.clear();
				cout<<"File.Size"<< file.size()<<endl;
									
				}else if (buf[0] == 'q') {
				exit(0);
			} else {
				cout << "Wrong Input" << endl;
			}
			alarm(1);
		}

	} else if (cpid > 0) {	//1.Parent
		while (true) {
			cin >> input;
			write(mypipe[1],&input, 4);
			
			if (input == 'q') {break;} 
		}
	} else {
		perror("fork"); exit(EXIT_FAILURE);
	} 

    return 0;
}
