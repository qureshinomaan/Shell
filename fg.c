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
struct stat statRes;


extern void fg(char *argv[], int len)
{
	int status, error;
	if(len!=2)
		printf("Wrong Number of Arguments!\n");
	pid_t pid= atoi(argv[1]);
	if(getpgid(pid)!= getpid())
		tcsetpgrp(0, pid);
	kill(pid, SIGCONT);
	waitpid(-1, &status, WUNTRACED );
	if(getpgid(pid)!= getpid())
	{
		printf("here\n");
		kill(getpid(), SIGCONT);
		tcsetpgrp(0, getpid());
		printf("here1\n");
		printf("here2\n");
	}
	return;
}