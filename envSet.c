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

extern void envSet(char *argv[], int len)
{
	if(len != 2 && len != 3)
		printf("Error!! Unsufficient Number of arguments.\n");
	if(len == 2)
		setenv(argv[1], "", 1);
	else if (len == 3)
		setenv(argv[1], argv[2], 1);
}

extern void unenvSet(char *argv[], int len)
{
	if(len == 1)
		printf("Error!! Unsufficient Number of Arguments.\n");
	if(unsetenv(argv[1]) == 0);
	else 
		printf("unsetenv failed!\n");
}