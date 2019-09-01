#include<stdlib.h>
#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<sys/resource.h>
#include<sys/types.h>

struct stat statRes;
struct rusage usage;
char command[100],cpy_cmd[100];
char home[100],pwd[100],dir[100],user[256],host[256];
int id;


void ls();
void hme();
void cd();
void pinfo2();
void username();
void vi();
void hostname();
void echo();
void vim();
void showpwd();
void printEveryTime();
void pinfo();
void history();
void addTohist();


extern void pd()
{
  char cwd[256];
  if (chdir("./") != 0)
    perror("chdir() error()");
  else {
    if (getcwd(pwd, sizeof(pwd)) == NULL)
      perror("getcwd() error");
  }
}