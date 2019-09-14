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
extern int amIPiped[100], isNxtPiped[100];
extern int piping[100][2];
extern int cmdcnt;

extern void  INThandlerz(int sig)
{
	signal(SIGTSTP, INThandlerz);
}