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
	int count=0;
	printf("%d\n", pidnumber);
	for (int i=0;i<pidnumber;i++)
	{
		if(pidlst[i][0]==0)
		{
			count++;
			printf("[%d] Running %s with pid [%d] \n", count, pidname[i], pidlst[i][1]);
		}
	}
}