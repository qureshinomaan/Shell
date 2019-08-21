#include<dirent.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<sys/types.h>

struct stat statRes;
struct rusage usage;
char command[100],cpy_cmd[100];
char home[100],pwd[100],dir[100],user[256],host[256];

int id=1;

long long int len(char string[])
{
	long long int i;
	while(string[i] == '\0')
		i++;
	return i;
}


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
 
void ls()
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

void hme()
{
	
  char cwd[256];

  if (chdir("./") != 0)
    perror("chdir() error()");
  else {
    if (getcwd(home, sizeof(home)) == NULL)
      perror("getcwd() error");
  }
}

void pd()
{
  char cwd[256];
  if (chdir("./") != 0)
    perror("chdir() error()");
  else {
    if (getcwd(pwd, sizeof(pwd)) == NULL)
      perror("getcwd() error");
  }
}



void cd()
{
	int i;
	char actual[100];
	if(chdir(dir)!=0)
		perror("cd ");
}




void username()
{
	if(getlogin_r(user,256) != 0)
		perror("");
}

void vi(char *argv[])
{
	pid_t cpid;
	int *stat;
	int status;
	id = fork();
	if(id==0)
  		{
  			execvp(argv[0],argv);
  			printf("yahin hoon main\n");
  		 }
  	else
  		{
  			wait(&status);
  			printf("wapas\n");
  			 if (WIFEXITED(status)) {
                printf("exited, status=%d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("killed by signal %d\n", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {
                printf("continued\n");
            }
  		}
}

void hostname()
{
	if(gethostname(host,256)!= 0)
		perror("");

}

void echo(char hello[])
{
	int i=0,status=0;
	while(hello[i]==' ')
		i++;
	for(i=i+5;i<strlen(hello);i++)
	{
		if(hello[i]=='\\')
		{
			i++;
			if(i<strlen(hello))
				printf("%c",hello[i]);
		}
		else if(hello[i]=='\"')
			status=!status;
		else if(status==1)
			printf("%c",hello[i]);
		else
		{
			int t=0;
			printf("%c",hello[i]);
			while(hello[i+1]==' ')
				{i++;t++;}
			if(t==1)
				i--;
		}
	}
}

void showpwd()
{
	if(strcmp(home,pwd) == 0)
		write(1,"~\n",3);
	else if (strcmp(pwd,home) < 1)
	{
		printf("\033[1;32m%s\n",pwd);
	}
	else 
	{
		char tobeprinted[100];
		int i;
		printf("\033[1;32m~");
		for(i=strlen(home);i<strlen(pwd);i++)
			{
				printf("\033[1;32m%c",pwd[i]);
			}
		printf("\033[1;32m\n");
	}

}

void printEveryTime()
{
	pd();
	printf("\033[1;31m%s",user);
	printf("\033[1;35m@");
	printf("\033[1;36m%s",host);
	if(strcmp(home,pwd) == 0)
		printf("\033[1;32m<~>");
	else if (strcmp(pwd,home) < 1)
	{
		printf("\033[1;32m<%s>",pwd);
	}
	else 
	{
		char tobeprinted[100];
		int i;
		printf("\033[1;32m<~");
		for(i=strlen(home);i<strlen(pwd);i++)
			{
				printf("\033[1;32m%c",pwd[i]);
			}
		printf("\033[1;32m>");
	}
	printf("\033[1;34m");

}


void pinfo()
{
	char in[30];
	printf("PID %lu\n",getpid());
	FILE* status;
	status=fopen( "/proc/self/status", "r" );
	if(status!=NULL)
		fgets(in,30,status);
}

int main(void)
{
	hme();
	username();
	hostname();
	while(1)
	{
		char *every, *semicolon;
		char *actual_cmd[100],*sccmd[100];
		printEveryTime();
		//============================================================//
		// Getting the command and splitting it. 
		//============================================================//
		fgets(command,100, stdin);
		strcpy(cpy_cmd,command);
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
			{	if(strlen(actual_cmd[1])!=0)
					strcpy(dir,actual_cmd[1]);
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
			pinfo();
		}
		else
		{
			vi(actual_cmd);
		}

	}
	return 0;
}