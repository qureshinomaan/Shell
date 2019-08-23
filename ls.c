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

struct stat statRes;
struct rusage usage;
char command[100],cpy_cmd[100];
char home[100],pwd[100],dir[100],user[256],host[256];
int id;

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
 
extern void ls()
{
	DIR *dir;
	int l=0,a=0;
	int i=0;
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
	}
 	struct dirent *entry;
	if ((dir = opendir(pwd)) == NULL )
		perror("opendir() error");
	else {
	    while ((entry = readdir(dir)) != NULL)
	      {
	      	if(a==0)
	      	{
	      		if(entry->d_name[0]!='.')
	      		{
	      			printf("  %10s ", entry->d_name);
      			if(l==1)
	      			{
	      			    stat(entry->d_name,&statRes);
	      			    fileProperties(statRes);
	      			}
	      		printf("\n");
	      		}
	      	}
	  		else
	  		{
	  			printf("  %10s ", entry->d_name);
	      		if(l==1)
	      		{
	      			stat(entry->d_name,&statRes);
	      			fileProperties(statRes);
	      		}
	      		printf("\n");
	  		}
	      }
	    closedir(dir);
	}
}