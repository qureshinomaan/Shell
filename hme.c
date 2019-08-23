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
void pd();
void cd();
void username();
void vi();
void vim();
void pinfo2();
void hostname();
void echo();
void showpwd();
void printEveryTime();
void pinfo();
void history();
void addTohist();


extern void hme()
{
	
  char cwd[256];

  if (chdir("./") != 0)
    perror("chdir() error()");
  else {
    if (getcwd(home, sizeof(home)) == NULL)
      perror("getcwd() error");
  }
}