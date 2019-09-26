#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include<sys/resource.h>
#include<time.h>
#include<sys/types.h>

int current_fg;
int amIPiped[100], isNxtPiped[100];
int piping[100][2];
int cmdcnt;
char pidname[1000][200];
int pidnumber;
char command[100],cpy_cmd[100];
int pidlst[20000][3];
int current_fg;

extern void  INThandlerz(int sig)
{

		pidlst[pidnumber][0] = current_fg;
	    pidlst[pidnumber][1] = current_fg;
	    pidlst[pidnumber][2] = getpid();
	    strcpy(pidname[pidnumber], cpy_cmd);
	    pidnumber++;
	signal(SIGTSTP, INThandlerz);
}