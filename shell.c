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

extern struct stat statRes;
extern struct rusage usage;
extern char *command,cpy_cmd[100];
extern char home[100],pwd[100],dir[100],user[256],host[256];
extern int pidlst[20000][2];
extern int pidnumber;
extern char pidname[1000][200];
extern char input_file[100], output_file[100]; 
extern int inputD, outputD;

//============================================================//
// Summary about each of the variable used. 
// statRes ans usage are used in ls to get the information about the file. 
// command contains a single command after strtok(semicolon).
// cpy_cmd contains the copy of the full command. 
// home contains hoem name, pwd contains present working directory.
// dir, user, host are similar variables for working with directories. 
// pidlst pidname contains the background processes. 
// input_file contains the name of input redirection file. 
// output_file contains the name of output redirection file. 
//============================================================//


void pidover()
{
	for (int i=0;i<pidnumber;i++)
	{
		if(pidlst[i][0]==0)
		{
			if(kill(pidlst[i][1], 0)!=0)
			{
				printf("%s with pid %d exied \n", pidname[i], pidlst[i][1]);
				pidlst[i][0]=1;
			}
		}
	}
}

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
void vim();
void hostname();
void echo();
void showpwd();
void printEveryTime();
void pinfo();
void history();
void addTohist();
void envSet();
void unenvSet();
void kjob();
void jobs();
void overkill();

int main(void)
{
	hme();
	username();
	hostname();
	int pid, status;
	while(1)
	{
		strcpy(input_file, "\0");
		strcpy(output_file, "\0");
		pidover();
		int direction =0;
		char *every, semicolon[100]; 
		char *actual_cmd[100],*sccmd[100];
		printEveryTime();
		fgets(semicolon,100,stdin);
		char *everysemi = semicolon;
		inputD=0; outputD=0;
//============================================================================================//
// Getting multiple commands and splitting it. 
//============================================================================================//
		while((command = strtok_r(everysemi, ";",&everysemi)))
		{
			addTohist(command);
			//============================================================//
			// Getting the single command and splitting it. 
			// cpy_cmd contains the copy of the command we get. 
			//============================================================//
			if(command[strlen(command)-1] == '\n')
				command[strlen(command)-1]='\0';

			if(strlen(command)!=0)
			{	
					

//============================================================================================//
// Command Parsing starts here.
//============================================================================================//


					strcpy(cpy_cmd,command);  
					every = strtok(command, " ");
					int len=0;
					while(every!=0)
					{
						if(strcmp(every,"\n")!=0)
						{
							if(every[strlen(every)-1]=='\n')
								every[strlen(every)-1]='\0';	
						//============================================================//
						// Checking input, output redirection here. 
						// direction = 1 means we need to take the input. 
						// direction = 2 means we need to give the output. 
						// direction = 3 means we ened to append the output
						//============================================================//
						if(direction == 1)
							{strcpy(input_file, every); direction = 0; inputD = 1; }
						else if(direction == 2)
							{strcpy(output_file, every); direction = 0; outputD = 1; }
						else if(direction ==3 )
							{strcpy(output_file, every); direction = 0; outputD = 2;}
			
						if(strcmp(every,"<")==0)
							direction = 1;
						else if(strcmp(every, ">")==0)
							direction = 2;
						else if(strcmp(every, ">>")==0)
							direction = 3;

						if(direction == 0 && !inputD && !outputD)
						{
							actual_cmd[len] = every;	
							if(actual_cmd[len][strlen(actual_cmd[len])-1]=='\n')
								actual_cmd[len][strlen(actual_cmd[len])-1]='\0';
							len++;
						}
						//============================================================//

						}
						every = strtok(0, " ");		
					}
					actual_cmd[len]=NULL;
		
					
//============================================================================================//
// Command parsing ends here.
//============================================================================================//


//============================================================================================//
// Checking the command and executing it starts here. 
//============================================================================================//
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
					else if(strcmp(actual_cmd[0],"quit") == 0)
						_exit(0);
					else if(strcmp(actual_cmd[0],"pwd") == 0)
						showpwd();
					else if(strcmp(actual_cmd[0],"ls") == 0)
						ls(actual_cmd[1]);
					else if(strcmp(actual_cmd[0],"pinfo") == 0)
					{
                        if(len<2)
                            pinfo();
                        else if(strlen(actual_cmd[1])==0)
                        {  pinfo();}
						else
							pinfo2(actual_cmd[1]);

					}
					else if(strcmp(actual_cmd[0], "history")==0)
					{
						if(len == 1)
							history(10);
						else if(len == 2)
						{
							if(strlen(actual_cmd[1])>0)
								{
									history(atoi(actual_cmd[1]));
								}
							else 
								history(10);
						}
					}
					else if (strcmp(actual_cmd[0], "setenv") == 0)
					{
						envSet(actual_cmd, len);
					}
					else if(strcmp(actual_cmd[0], "unsetenv") == 0)
					{
						unenvSet(actual_cmd, len);
					}
					else if(strcmp(actual_cmd[0], "kjob") == 0)
					{
						kjob(actual_cmd, len);
					}
					else if(strcmp(actual_cmd[0], "jobs") == 0)
					{
						jobs();
					}
					else if(strcmp(actual_cmd[0], "overkill")==0)
					{
						overkill();
					}
					else
					{
						if(len>1 && strcmp( actual_cmd[1],"&") ==0 )
							vi(actual_cmd,len);
						else
							vim(actual_cmd, len);
					}
//============================================================================================//
// Command Execution ends here.
//============================================================================================//	
				}
		}
	}

	return 0;
}
