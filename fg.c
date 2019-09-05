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
int pidlst[20000][2];


extern void fg(char *argv[], int len)
{
	if(len!=2)
		printf("Wrong Number of Arguments!\n");
	pid_t pid= atoi(argv[1]);
	printf("GPID OF %d is %d\n",pid, getpgid(pid));
	printf("GPID OF 0 is %d\n", getpgid(0));
	int err = tcsetpgrp(STDOUT_FILENO,getpid());
	printf("GPID OF %d is %d\n", pid, getpgid(0));

	return;
}