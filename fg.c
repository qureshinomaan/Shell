#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/resource.h>

char pidname[1000][200];
int pidnumber;
int pidlst[20000][3];
int pids[1000];
struct stat statRes;


extern void fg(char *argv[], int len)
{
	int status, error;
	if(len!=2)
	{	printf("Wrong Number of Arguments!\n"); return;}
	int jobno= atoi(argv[1]);
	pid_t pid = pids[jobno];
	//pid_t pid = atoi(argv[1]);
	if(kill(pid, 0) !=0 )
	{
		printf("Sorry, This job does not exist.\n");
		return;
	}
	if(getpgid(pid)!= getpid())
		tcsetpgrp(0, pid);
	kill(pid, SIGCONT);
	waitpid(pid, &status, WUNTRACED);
	signal(SIGTTOU, SIG_IGN);
	pid_t stdin_PGID;
	stdin_PGID = tcgetpgrp(STDIN_FILENO);
     if (stdin_PGID == -1) {
        printf("Could not get PGID for stdin.n");
       // return(EXIT_FAILURE);
     }
	else if (tcsetpgrp(STDIN_FILENO, getpid()) == -1) {
        printf("Could not set PGID.n");
       // return(EXIT_FAILURE);
     }
	signal(SIGTTOU, SIG_DFL);
	return;
}