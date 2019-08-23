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

extern struct stat statRes;
extern struct rusage usage;
extern char *command,cpy_cmd[100];
extern char home[100],pwd[100],dir[100],user[256],host[256];


long long int len(char string[])
{
	long long int i;
	while(string[i] == '\0')
		i++;
	return i;
}

void pinfo2(char *pid);
void ls();
void hme();
void pd();
void cd();
void username();
void vi();
void hostname();
void echo();
void showpwd();
void printEveryTime();
void pinfo();
void history();
void addTohist();

int main(void)
{
	hme();
	username();
	hostname();
	while(1)
	{
		char *every, semicolon[100];
		char *actual_cmd[100],*sccmd[100];
		printEveryTime();
		fgets(semicolon,100,stdin);
		char *everysemi = semicolon;
		while((command = strtok_r(everysemi, ";",&everysemi)))
		{
			addTohist(command);
			//============================================================//
			// Getting the command and splitting it. 
			//============================================================//
			if(command[strlen(command)-1] == '\n')
				command[strlen(command)-1]='\0';

			if(strlen(command)!=0)
		{	strcpy(cpy_cmd,command);
					every = strtok(command, " ");
					int len=0;
					while(every!=0)
					{
						if(strcmp(every,"\n")!=0)
						{
							actual_cmd[len] = every;
							if(actual_cmd[len][strlen(actual_cmd[len])-1]=='\n')
								actual_cmd[len][strlen(actual_cmd[len])-1]='\0';
							len++;
						}
						every = strtok(0, " ");		
					}
					actual_cmd[len]=NULL;
		
					//============================================================//
		
					//============================================================//
					// Actual command in the making. 
					//============================================================//
					if(strcmp(actual_cmd[0],"cd") == 0)
					{
						if(len == 1)
						{
							strcpy(dir,home);
							cd();
						}
						else
						{	
							if(strlen(actual_cmd[1])!=0 && actual_cmd[1][0]!='~')
								strcpy(dir,actual_cmd[1]);
							else if(actual_cmd[1][0]=='~'&&strlen(actual_cmd[1])!=1)
							{
								char newcommand[100];
								newcommand[0] = '/';
								for(int i=1;i<strlen(actual_cmd[1]);i++)
									newcommand[i] = actual_cmd[1][i];
								strcpy(dir, home);
								strcat(dir, newcommand);
							}
							else 
								strcpy(dir,home);
							cd();
						}
					}
					else if(strcmp(actual_cmd[0],"echo") == 0)
						echo(cpy_cmd);
					else if(strcmp(actual_cmd[0],"exit") == 0)
						_exit(0);
					else if(strcmp(actual_cmd[0],"pwd") == 0)
						showpwd();
					else if(strcmp(actual_cmd[0],"ls") == 0)
						ls();
					else if(strcmp(actual_cmd[0],"pinfo") == 0)
					{
						if(strlen(actual_cmd[1])==0)
							pinfo();
						else
							pinfo2(actual_cmd[1]);

					}
					else if(strcmp(actual_cmd[0], "history")==0)
					{
						history();
					}
					else
					{
						vi(actual_cmd);
					}	
				}
		}
	}

	return 0;
}