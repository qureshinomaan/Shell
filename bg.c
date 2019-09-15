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


extern void bg(char *argv[], int len)
{
	int status, error;
	if(len!=2)
		printf("Wrong Number of Arguments!\n");
	int jobno= atoi(argv[1]);
	pid_t pid = pidlst[jobno-1][1];
	kill(pid, SIGCONT);
	return;
}