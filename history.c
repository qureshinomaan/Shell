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

void vi();
void vim();

int minimum(int a, int b)
{
	if(a<b)
		return b;
	return a;
}

int mini(int a, int b)
{
    if(a<b)
        return a;
    return b;
}

extern void history(int last)
{
	char path[100];
	char currentCharacter;
	char hello[10][200];
	char temp[200];
	int totalLinesCount=0;
	strcpy(path, home);
	strcat(path, "/history.txt");
	FILE *f1=fopen(path,"r");
	while(fgets(temp, sizeof(temp), f1) != NULL)
	{
            totalLinesCount ++;
    }
    fclose(f1);
	FILE *f2 = fopen(path, "r");

    int curr = minimum(0, totalLinesCount-10);
    int counter=0,lines=0;
    while(fgets(temp, sizeof(temp), f2) != NULL)
    {
    	if(counter>=curr)
    	{	
    		strcpy(hello[lines], temp);
    		lines++;
    	}
    	counter++;
    }
    int x = mini(last, lines);
    printf("last - x = %d\n", last);
    for(int i =10 - last ;i<10;i++)
    	printf("%s", hello[i]);
    return ;
}



extern void addTohist(char cmd[])
{
	char path[100];
	char currentCharacter;
	char hello[10][200];
	char temp[200];
	int totalLinesCount=0;
	strcpy(path, home);
	strcat(path, "/history.txt");
	FILE *f1=fopen(path,"r");
	while(fgets(temp, sizeof(temp), f1) != NULL)
	{
            totalLinesCount ++;
    }
    if(totalLinesCount>=20)
    {

    	fclose(f1);
    	char newname[100];
    	strcpy(newname, home);
    	strcat(newname, "/history2.txt");
    	FILE *f2=fopen(path,"r");
		FILE *newfile = fopen(newname, "a");
		int lines =0 ;
		while(fgets(temp, sizeof(temp), f2) != NULL)
    	{
    		if(lines>=1)
	    		fputs(temp, newfile);
	    	lines++;
   	 	}
   	 	fputs(cmd,newfile);
   	 	fclose(f2);
   	 	remove(path);
   	 	fclose(newfile);
   	 	rename(newname, path);
    }
    else
    { 
    	fclose(f1);
    	FILE *f3 = fopen(path,"a");
        fputs(cmd, f3);
        if(ferror(f3) == EOF)
        	printf("error here\n");
        fclose(f3);
    }
	return;
}


extern void upArrow(int command_where)
{
    printf("here\n");
    char *command[100], *every;
    char path[100];
    char currentCharacter;
    char hello[10][200];
    char temp[200];
    int totalLinesCount=0;
    strcpy(path, home);
    strcat(path, "/history.txt");
    FILE *f1=fopen(path,"r");
    while(fgets(temp, sizeof(temp), f1) != NULL)
    {
            totalLinesCount ++;
    }
   FILE *f2 = fopen(path, "r");
   int count =0;
   while(fgets(temp, sizeof(temp), f2) != NULL && totalLinesCount - command_where  !=count )
   {
    count++;
   }
   printf("%s\n",temp);
    every = strtok(temp, " ");
    int len =0, i=0;
    while(every!=NULL)
    {
        command[i] = (char*)malloc(100);
        strcpy(command[i], every);
        i++;
        every = strtok(0, " "); 
    }
    command[i] = NULL;
    vim(command, i);

    return;
}
