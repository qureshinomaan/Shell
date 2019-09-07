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
	int status;
	if(len!=2)
		printf("Wrong Number of Arguments!\n");
	pid_t pid= atoi(argv[1]);
	int error = tcsetpgrp(0, pid);
	if(error == -1)
		perror("");
	kill(pid, SIGCONT);
	waitpid(-1, &status, WUNTRACED );
	if(getpgid(pid)!= getpid())
	{
		printf("here\n");
		tcsetpgrp(0, getpid());
		error= kill(getpid(), SIGCONT);
		if(error == -1)
		perror("");
	}
	return;
}