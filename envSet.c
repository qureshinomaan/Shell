#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<signal.h>
#include<sys/resource.h>
#include<time.h>
#include<sys/types.h>


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

extern void envSet(char *argv[], int len)
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
			fdin = open(input_file, O_RDWR);
			dup2(fdin, 0);
			close(fdin);
		}
		if(outputD == 1 || outputD == 2)
		{
			// You must give at least one of O_WRONLY, O_RDONLY, O_RDWR
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
			dup2(piping[cmdcnt-1][0], 0);
			close(piping[cmdcnt-1][1]);
			close(piping[cmdcnt-1][0]);
		}
		if(isNxtPiped[cmdcnt] == 1)
		{
			dup2(piping[cmdcnt][1], 1);
			close(piping[cmdcnt][0]);
			close(piping[cmdcnt][1]);
		}

		//============================================================//
    	// Piping ends here. 
		//============================================================//

		if(len != 2 || len != 3)
			printf("Error!! Unsufficient Number of arguments.\n");
		if(len == 2)
			setenv(argv[1], "", 1);
		else if (len == 3)
			setenv(argv[1], argv[2], 1);
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
          // while(cpid!=cid)
          // {
          //   cpid = wait(&status);
          //   if(cpid != cid)
				      // kill(cpid, SIGKILL);
          // }
        }
}

extern void unenvSet(char *argv[], int len)
{
	if(len == 1)
		printf("Error!! Unsufficient Number of Arguments.\n");
	if(unsetenv(argv[1]) == 0);
	else 
		printf("unsetenv failed!\n");
}