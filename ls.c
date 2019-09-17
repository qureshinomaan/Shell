#include<stdlib.h>
#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<sys/resource.h>
#include<sys/types.h>

struct dirent *ent;

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

void hme();
void pd();
void cd();
void username();
void vi();
void vim();
void hostname();
void pinfo2();
void echo();
void showpwd();
void printEveryTime();
void pinfo();
void history();
void addTohist();



void fileProperties(struct stat stats)
{
	struct tm dt;
	//Read write permission of files.
	if(S_ISREG(stats.st_mode) == 1)
		printf("-");
	else
		printf("D");
	printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
    printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
    printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
    printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
    printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
    printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
    printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
    printf( (stats.st_mode & S_IROTH) ? "r" : "-");
    printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
    printf( (stats.st_mode & S_IXOTH) ? "x" : "-");

	//file size 
	printf("  %10d", stats.st_size);

	//Create time 
	dt = *(gmtime(&stats.st_ctime));
    printf("%d-%d-%d %d:%d:%d     ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                              dt.tm_hour, dt.tm_min, dt.tm_sec);
    //Modify time
    dt = *(gmtime(&stats.st_mtime));
    printf("%d-%d-%d %d:%d:%d    ", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                              dt.tm_hour, dt.tm_min, dt.tm_sec);

}
 
extern void ls(char actual_cmd[])
{

	pid_t cpid;
	int status;
	struct stat statRes;
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
		
	DIR *dir;
	int l=0,a=0;
	int i=0;
	int isdir=0;
	while(cpy_cmd[i]==' ')
		i++;
	i+=3;
	for(;i<strlen(cpy_cmd);i++)
	{
		if(cpy_cmd[i]=='-')
		{
			if(cpy_cmd[i+1]=='l')
				{	
					l=1;
					if(cpy_cmd[i+2]=='a')
						a=1;
				}
			else if(cpy_cmd[i+1]=='a')
				{	
					a=1;
					if(cpy_cmd[i+2]=='l')
						l=1;
				}
		}
		else if(cpy_cmd[i-1] == ' ' && cpy_cmd[i]!='\n')
			isdir =1;
	}

 	//
	if ((dir = opendir(pwd)) == NULL )
		perror("opendir() error");
	else {		
	    while ((ent = readdir(dir)) != NULL)
	      {
	      	if(a==0)
	      	{
	      		if(ent->d_name[0]!='.')
	      		{
	      			if(isdir==0)
	      			{
	      				printf("  %10s ", ent->d_name);
	      				char *this1;
	      				this1 =  ent->d_name;
	      			     if(l==1)
	      				 {
	      				     stat(this1,&statRes);
	      				     fileProperties(statRes);
	      				  }
	      				printf("\n");
	      			}
	      			else if(isdir == 1)
	      			{
	      				printf("  %10s ", ent->d_name);
	      				char this1[100];
	      				strcpy(this1, ent->d_name);
	      			     if(l==1)
	      				 {
	      				     stat( this1,&statRes);
	      				     fileProperties(statRes);
	      				  }
	      				printf("\n");
	      			}
	      		}
	      	}
	  		else
	  		{
	  			if(isdir == 0 )
	  			{	
		  			printf("  %10s ", ent->d_name);
		      		if(l==1)
		      		{
		      			 stat(ent->d_name,&statRes);
		      			 fileProperties(statRes);
		      		}
		      		printf("\n");
	  			}
	  			else if(isdir==1)
	  			{
	  				printf("  %10s ", ent->d_name);
		      		if(l==1)
		      		{
		      			 stat(ent->d_name,&statRes);
		      			 fileProperties(statRes);
		      		}
		      		printf("\n");
	  			}
	  		}
	      }
	    closedir(dir);
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