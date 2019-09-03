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


struct stat statRes;
struct rusage usage;
char command[100],cpy_cmd[100];
char home[100],pwd[100],dir[100],user[256],host[256];
int id;
char input_file[100], output_file[100]; 
int inputD, outputD;

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
	//printf("bhow\n");
    pid_t cid = fork();
    if(cid==0)
    {  
		int fdin,fdout;
		if(inputD == 1)
		{
			fdin = open(input_file, O_RDWR);
			dup2(fdin, 0);
			close(fdin);
		}
		if(outputD == 1)
		{
			fdout = open(output_file,O_RDWR);
			dup2(fdout, 1);
			close(fdout);
		}
		// printf("yahin honn main\n");
		execvp(argv[0],argv);
		// printf("foreground se khatam\n");
		_exit(0);
         
    }
    else
        {
          cpid = wait(&status);
          while(cpid!=cid)
          {
            cpid = wait(&status);
            if(cpid != cid)
				      kill(cpid, SIGKILL);
          }
        }
}
