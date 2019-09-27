#include<dirent.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/resource.h>

char pidname[1000][200];
int pidnumber;
int pidlst[20000][2];
int pids[1000];


void printJob(char *pid)
{
		FILE *status;
        char process[100], *printed;
      //  printf("PID %s\n",pid);
        //sprintf(pid, "%d", pi);
        strcpy(process,"/proc/");
    	strcat(process,pid);
        strcat(process, "/status");
        status=fopen( process, "r" );
        size_t ptr;
        if(status != NULL)
        {
                while(getline(&printed, &ptr, status)!=-1)
                {
                        if(strncmp(printed, "State",5) == 0)
                            printf("%s ", printed);
                }
        }
 
}

extern void jobs()
{
	for (int i=0;i<pidnumber;i++)
	{
		if(kill(pids[i], 0) == 0)
			{
				printf("[%d] ", i);
				char stringpid[30];
				sprintf(stringpid, "%d", pids[i]);
				printJob(stringpid);
				printf("%s with pid [%d] \n",pidname[i], pids[i]);
			}
	}
}

