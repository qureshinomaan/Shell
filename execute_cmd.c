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
char *command,cpy_cmd[100];
char home[100],pwd[100],dir[100],user[256],host[256];
int pidlst[20000][3];
int pidnumber;
char pidname[1000][200];
char input_file[100], output_file[100]; 
int inputD, outputD;
int current_fg;

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
void cronJob();
void upArrow();




extern void execute_cmd(char *actual_cmd[], int len)
{
	if( actual_cmd[0] == NULL)
		return ;
	printf("Command is : %d\n", (int)actual_cmd[0][0]);
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
						{
							echo(actual_cmd, len);
						}
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
					else if(strcmp(actual_cmd[0], "fg") == 0)
					{
						fg(actual_cmd, len);
					}
					else if(strcmp(actual_cmd[0], "bg") == 0)
					{
						bg(actual_cmd, len);
					}
					else if(strcmp(actual_cmd[0], "cronjob") == 0)
					{
						cronJob(actual_cmd, len);
					}
					else if((int)actual_cmd[0][0]==27 && (int)actual_cmd[0][1]==91 && (int)actual_cmd[0][2]==65)
					{
						int count =0;
						for(int i=0; i<strlen(actual_cmd[0]); i++)
						{
							if((int)actual_cmd[0][0]==27 && (int)actual_cmd[0][1]==91 && (int)actual_cmd[0][2]==65)
								count++;
						}
						upArrow(count);
					}
					else
					{
						if(len>1 && strcmp( actual_cmd[len-1],"&") == 0 )
							{
								actual_cmd[len-1] = NULL;
								vi(actual_cmd,len);
							}
						else
							vim(actual_cmd, len);
					}
}