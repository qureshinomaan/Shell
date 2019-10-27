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

void execute_cmd();
void vi();

extern void cronJob(char *argv[], int len)
{
	char *actual_cmd[100], cmdlen=0;
	char *sleep_cmd[100];
	int i =2;

	while(strcmp(argv[i], "-t")!=0)
	{
		printf("%s\n", argv[i]);
		actual_cmd[cmdlen]= (char *)(malloc(100));
		strcpy(actual_cmd[cmdlen], argv[i]);
		cmdlen++;
		i++;
	}

	actual_cmd[i-2] = NULL; i++;
	sleep_cmd[1] = (char *)(malloc(100));
	sleep_cmd[0] = (char *)(malloc(100));
	int interval = atoi(argv[i]);  strcpy(sleep_cmd[1], argv[i]); i++;
	int totalTime = atoi(argv[i+1]);
	int timenow = 0;
	strcpy(sleep_cmd[0], "sleep");
	sleep_cmd[2] = NULL;

	while(timenow<totalTime)
	{
		vi(sleep_cmd, 3);
		execute_cmd(actual_cmd, cmdlen);
		timenow += interval;
	}
	printf("CronJob Task Complete\n");
}
