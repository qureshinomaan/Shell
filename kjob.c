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

extern void kjob(char *argv[], int len)
{
	if(len != 3)
		printf("Insufficient Number of arguments.\n");
	else 
	{
		int sig = atoi(argv[2]);
		pid_t pid = atoi(argv[1]);
		kill(pid, sig);
	}
}