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

char pidname[1000][200];
int pidnumber;
int pidlst[20000][3];
int pids[1000];
struct stat statRes;

extern void kjob(char *argv[], int len)
{
	if(len != 3)
		printf("Insufficient Number of arguments.\n");
	else 
	{
		int sig = atoi(argv[2]);
		int jobno = atoi(argv[1]);
		int pid = pids[jobno];
	//	pid_t pid = pidlst[jobno-1][1];
		kill(pid, sig);
	}
}