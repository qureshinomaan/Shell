#include<stdlib.h>
#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>
#include<sys/resource.h>


struct stat statRes;
struct rusage usage;
char command[100],cpy_cmd[100];
char home[100],pwd[100],dir[100],user[256],host[256];
int id;

void ls();
void hme();
void pd();
void username();
void pinfo2();
void vi();
void vim();
void hostname();
void echo();
void showpwd();
void printEveryTime();
void pinfo();
void history();
void addTohist();
void vim();



extern void cd()
{
	int i;
	char actual[100];
	if(chdir(dir)!=0)
		perror("cd ");
}