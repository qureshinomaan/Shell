#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
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
void pd();
void cd();
void username();
void vi();
void vim();
void hostname();
void echo();
void showpwd();
void printEveryTime();
void history();
void addTohist();


extern void pinfo()
{
	FILE *status;
	char process[100], *printed,pid[100];
	printf("PID %lu\n",getpid());
	strcpy(process,"/proc/");
	sprintf(pid, "%d", getpid());
	strcat(process,pid);
	strcat(process, "/status");
	status=fopen( process, "r" );
	size_t ptr;
	if(status!=NULL)
		{
			while(getline(&printed, &ptr, status)!=-1)
			{
				if(strncmp(printed, "State",5) == 0)
					printf("%s\n", printed);
				else if(strncmp(printed, "VmSize",6) == 0)
					printf("%s\n", printed);
			}
			strcpy(process, "/proc/");
			strcat(process, pid);
			strcat(process, "/exe");
			readlink(process,printed, 100);
			printf("Executable Path: %s\n", printed);
		}
}

extern void pinfo2(char *pid)
{

	pid_t cpid;
	int *stat;
//	int status;
	//============================================================//
    	// Input, Output redirection starts here. 
	//============================================================//
	printf("here1\n");
		int fdin,fdout;
		if(inputD == 1)
		{
			fdin = open(input_file, O_RDWR);
			dup2(fdin, 0);
			close(fdin);
		}
	printf("here1\n");

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
	printf("here3\n");

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
	printf("here4\n");
		

		FILE *status;
		char process[100], *printed;
		printf("PID %s\n",pid);
		strcpy(process,"/proc/");
		//sprintf(pid, "%d", pi);
	    strcat(process,pid); 
		strcat(process, "/status");
		status=fopen( process, "r" );
		size_t ptr;
		if(status != NULL)
		{	
			while(getline(&printed, &ptr, status)!=-1)
			{
				if(strncmp(printed, "State",5) == 0)
					printf("%s\n", printed);
				else if(strncmp(printed, "VmSize",6) == 0)
					printf("%s\n", printed);
			}
			strcpy(process, "/proc/");
			strcat(process, pid);
			strcat(process, "/exe");
			readlink(process,printed, 100);
			printf("Executable Path: %s\n", printed);
		}

}
