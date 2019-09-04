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

extern void jobs()
{
	for (int i=0;i<pidnumber;i++)
	{
		if(pidlst[i][0]==0)
		{
			printf("%s with pid %d exied \n", pidname[i], pidlst[i][1]);
		}
	}
}