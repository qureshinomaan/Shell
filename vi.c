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
void hostname();
void echo();
void showpwd();
void printEveryTime();
void pinfo();


extern void vi(char *argv[])
{
	pid_t cpid;
	int *stat;
	int status;
	id = fork();
	if(id==0)
  		{
  			execvp(argv[0],argv);
  			printf("yahin hoon main\n");
  		 }
  	else
  		{
  			wait(&status);
  			printf("wapas\n");
  			 if (WIFEXITED(status)) {
                printf("exited, status=%d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("killed by signal %d\n", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {
                printf("continued\n");
            }
  		}
}