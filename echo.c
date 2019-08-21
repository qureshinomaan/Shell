#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>

struct stat statRes;
struct rusage usage;
char command[100],cpy_cmd[100];
char home[100],pwd[100],dir[100],user[256],host[256];
int id;

void ls();
void hme();
void pd();
void cd();
void username();
void vi();
void hostname();
void showpwd();
void printEveryTime();
void pinfo();


extern void echo(char hello[])
{
	int i=0,status=0;
	while(hello[i]==' ')
		i++;
	for(i=i+5;i<strlen(hello);i++)
	{
		if(hello[i]=='\\')
		{
			i++;
			if(i<strlen(hello))
				printf("%c",hello[i]);
		}
		else if(hello[i]=='\"')
			status=!status;
		else if(status==1)
			printf("%c",hello[i]);
		else
		{
			int t=0;
			printf("%c",hello[i]);
			while(hello[i+1]==' ')
				{i++;t++;}
			if(t==1)
				i--;
		}
	}
}