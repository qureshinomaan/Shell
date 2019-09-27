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
		FILE *status;
        char process[100], *printed;
        printf("PID %s\n",pid);
        strcpy(process,"/proc/");
        //sprintf(pid, "%d", pi);
    	strcat(process,pid);
        strcat(process, "/status");
        status=fopen( process, "r" );
        printf("process : %s\n", process);
        size_t ptr;
        if(status != NULL)
        {
                while(getline(&printed, &ptr, status)!=-1)
                {
       					 printf("here1\n");

                        if(strncmp(printed, "State",5) == 0)
                                printf("%s\n", printed);
                        else if(strncmp(printed, "VmSize",6) == 0)
                                printf("%s\n", printed);
             		   printf("here3\n");
                }
                printf("here2\n");
                strcpy(process, "/proc/");
                strcat(process, pid);
                strcat(process, "/exe");
                readlink(process,printed, 100);
                printf("Executable Path: %s\n", printed);
        }
 
}
