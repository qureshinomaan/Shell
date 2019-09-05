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
int pidlst[20000][2];

extern void overkill()
{
	int sig =9;
	for (int i=0;i<pidnumber;i++)
	{
		if(pidlst[i][0]==0)
		{
			pid_t pid =pidlst[i][1];
			kill(pid, sig);
		}
	}
}