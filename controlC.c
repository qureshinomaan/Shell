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


extern void  INThandler(int sig)
{
	 printf("Your signal number is : %d\n", sig);
     signal(sig, SIG_IGN);
     kill(getpid(), SIGINT);
     printf("You Pressed Control+C\n");
     signal(SIGINT, INThandler);
}