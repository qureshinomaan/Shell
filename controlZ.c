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


extern void  INThandlerz(int sig)
{
	printf("meri pid %d\n", getpid());
     signal(sig, SIG_IGN); //sigign sets the ignore to signal
     setpgid(0 ,0);
     printf("merigpid : %d\n",getpgid(0) );
     printf("meri pid %d\n", getpid());
     signal(SIGTSTP, INThandlerz);
}