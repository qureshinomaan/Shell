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

struct stat statRes;
struct rusage usage;
char command[100],cpy_cmd[100];
char home[100],pwd[100],dir[100],user[256],host[256];
int id;

void ls();
void hme();
void pinfo2();
void pd();
void cd();
void username();
void hostname();
void echo();
void vi();
void showpwd();
void printEveryTime();
void history();
void pinfo();
void addTohist();


extern void vim(char *argv[], int len)
{
	pid_t cpid;
	int *stat;
	int status;
	printf("bhow\n");
    pid_t cid = fork();
    if(cid==0)
        {  
          printf("yahin honn main\n");
          kill(getpid(),SIGKILL);
          execvp(argv[0],argv);
          printf("foreground se khatam\n");
         }
      else
        {
        	wait(NULL);
          // cpid = wait(&status);
          // while(cpid!=cid)
          // {
          //   cpid = wait(&status);
          //   if(cpid != cid)
          //   kill(cpid, SIGKILL);
          // }
        }
}