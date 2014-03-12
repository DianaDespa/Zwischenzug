#include<stdio.h>
#include<stdlib.h>
#include "FromEnginetoXboard.h"
#include <signal.h>
#include <ctime>
#include <cstdlib> 
#include <string.h>
#include <fstream>
#include <io.h>
using namespace std;

int main(int argc, char** argv)
{
     //signal handling  SIGINT
     //daca nu e analizat crashuieste programul
     //ignora SIGINT altfel crasuieste dupa prima mutare a engine-ului
    //signal(SIGINT,SIG_IGN);
    //srand((unsigned)time(0));

	
	//fflush(stdout);
	char command[100];
	//char comm1[100]="feature myname=\"Flip4itEngine\" san=1 usermove=1\n";
	//char comm2[20]="feature done=1\n";
	//fputs(comm1,stdout);
	//fputs(comm2,stdout);
	int move= 0, go = 0;

	ofstream fout("afile.txt");
	
	_read(0, command,100);

	fout<<command<<endl;
	/*while(move==0 && go==0){
		
		_read(0, command,100);

		fout<<command<<endl;

		if((strstr(command,"usermove")!= NULL) && (command[0]=='u') ){
			move=1; break;
		}
		if((strstr(command,"move")!= NULL) && (command[0]=='m') ){
			move=1; break;
		}
		if(strcmp("go\n",command)==0){
            fout<<"yupiiii\n";        
			go=1;break;
		}
		if(strcmp("force\n",command)==0){
                }
                if(strcmp("computer\n",command)==0){
                }
                if(strcmp("white\n",command)==0){
                }
                if(strcmp("black\n",command)==0){
                }
                if(strcmp("new\n",command)==0){
                }

                if(strcmp("quit\n",command)==0){
                }
                if(strstr("time",command)!=NULL){
                }
                if(strstr("otime",command)!=NULL){
                }
	}*/
	fout<<"am iesit\n";
	_write(1,"move a7a6",9);
	fflush(stdout);
	fout.close();
	return 0;
}