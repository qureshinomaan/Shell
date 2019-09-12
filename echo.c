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
char input_file[100], output_file[100]; 
int inputD, outputD;
int current_fg;
int amIPiped[100] , isNxtPiped[100] ;
int piping[100][2];
int cmdcnt;

void ls();
void hme();
void pinfo2();
void pd();
void cd();
void username();
void vi();
void hostname();
void vim();
void showpwd();
void printEveryTime();
void pinfo();
void history();
void addTohist();


extern void echo(char *argv[], int len)
{

	

	pid_t cpid;
	int *stat;
	int status;
	//printf("bhow\n");
    pid_t cid = fork();
    if(cid==0)
    {  
	//============================================================//
    	// Input, Output redirection starts here. 
	//============================================================//
		int fdin,fdout;
		if(inputD == 1)
		{
			printf("In Input Redirection\n");
			fdin = open(input_file, O_RDWR);
			dup2(fdin, 0);
			close(fdin);
		}
		if(outputD == 1 || outputD == 2)
		{
			// You must give at least one of O_WRONLY, O_RDONLY, O_RDWR
			printf("In Output Redirection\n");
			if(outputD == 2)
				fdout = open(output_file,O_APPEND | O_WRONLY);
			else 
				fdout = open(output_file,O_WRONLY);
			if(fdout == -1)
			{
				mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
				fdout = creat(output_file, mode);
				close(fdout);
				fdout = open(output_file,O_RDWR);
			}
			dup2(fdout, 1);
			close(fdout);
		}
		//============================================================//
    	// Input, Output redirection ends here. 
		//============================================================//

		//============================================================//
    	// Piping starts here. 
		//============================================================//

		if(amIPiped[cmdcnt] == 1)
		{
			printf("In Input Pipe\n");
			dup2(piping[cmdcnt-1][0], 0);
			close(piping[cmdcnt-1][1]);
			close(piping[cmdcnt-1][0]);
		}
		if(isNxtPiped[cmdcnt] == 1)
		{
			printf("In Output Pipe\n");
			dup2(piping[cmdcnt][1], 1);
			close(piping[cmdcnt][0]);
			close(piping[cmdcnt][1]);
		}

		//============================================================//
    	// Piping ends here. 
		//============================================================//
		for(int k=1;k<len;k++)
			{
				printf("%s\n",argv[k]);
			}
		
		_exit(0);
	}
	else 
	{
		 if(amIPiped[cmdcnt] == 1)
          {
          	close(piping[cmdcnt-1][1]);
          	close(piping[cmdcnt-1][0]);
        }
        waitpid(-1, &status, WUNTRACED );
	}
}