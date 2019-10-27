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
extern int pidlst[20000][3];
extern int pidnumber;
extern int pids[1000]; // For the pid 
extern char pidname[1000][200];
extern char input_file[100], output_file[100]; 
extern int inputD, outputD;
extern int current_fg;
extern int amIPiped[100], isNxtPiped[100];
extern int piping[100][2];
extern int cmdcnt;

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
			//	printf("%s with pid %d exited \n", pidname[i], pidlst[i][1]);
			//	pidlst[i][0]=1;
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
void fg();
void bg();
void INThandler();
void INThandlerz();
void execute_cmd();


int main(void)
{
	signal(SIGINT, INThandler);
	signal(SIGTSTP, INThandlerz);
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
		char *actual_cmd[10][100],*sccmd[100];
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
					

//======================================_======================================================//
// Command Parsing starts here.
//============================================================================================//
					for(int i =0;i<=cmdcnt;i++)
						{isNxtPiped[i]=0; amIPiped[i]=0;}

					strcpy(cpy_cmd,command);  
					every = strtok(command, " ");
					int len=0;
					cmdcnt =0;
					while(every!=0)
					{

						int pipeD=0;
					//	printf("%s\n", every);

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
						else if(strcmp(every, "|") == 0)
						{

							isNxtPiped[cmdcnt] = 1;
							actual_cmd[cmdcnt][len]=NULL;
							pipe(piping[cmdcnt]);
							execute_cmd(actual_cmd[cmdcnt], len);
							cmdcnt++;
							len =0;
							amIPiped[cmdcnt] = 1;
							direction  = 0;
							pipeD =1;
							inputD = 0;
							outputD =0;
						}
						if(direction == 0 && !inputD && !outputD && !pipeD)
						{
							actual_cmd[cmdcnt][len] = every;
							//printf("actual_cmd = %s\n", actual_cmd[cmdcnt][len]);	
							if(actual_cmd[cmdcnt][len][strlen(actual_cmd[cmdcnt][len])-1]=='\n')
								actual_cmd[cmdcnt][len][strlen(actual_cmd[cmdcnt][len])-1]='\0';
							len++;
						}
						//============================================================//

						}
						every = strtok(0, " ");		
					}
					actual_cmd[cmdcnt][len]=NULL;
		
					
//============================================================================================//
// Command parsing ends here.
//============================================================================================//


//============================================================================================//
// Checking the command and executing it starts here. 
//============================================================================================//
					execute_cmd(actual_cmd[cmdcnt], len);
//============================================================================================//
// Command Execution ends here.
//============================================================================================//	
				}
		}
	}

	return 0;
}
