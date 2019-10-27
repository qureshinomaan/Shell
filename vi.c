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


struct stat statRes;
struct rusage usage;
char command[100],cpy_cmd[100];
char home[100],pwd[100],dir[100],user[256],host[256];
int id;
char pidname[1000][200];
int pidnumber;
int pidlst[20000][3];
int pids[1000];
char input_file[100], output_file[100]; 
int inputD, outputD;

void ls();
void hme();
void pinfo2();
void pd();
void cd();
void username();
void hostname();
void echo();
void vim();
void showpwd();
void printEveryTime();
void history();
void pinfo();
void addTohist();

volatile int total =0;

int pid[10000];


void sig_handler(int signum) {
  int pid = waitpid(-1, NULL, WNOHANG);
  if(pid > 0){
    //printf("Process {%s} Successfully exited with {%d} .\n",pidname[pid],pid);
  }
// printf("sig_handler se gaya\n");
}


extern void vi(char *argv[],int len)
{
	pid_t cpid;
	int *stat;
	int status;
  printf("%s\n",argv[1]);
    pid_t cid = fork();
    if(cid==0)
        { 
          //This is the child process. 
          setpgid(0,0);
          execvp(argv[0],argv);
          _exit(0);
        }
      else
        {
          // fork returns the process id of child to parent and 0 to child process. 
        //  kill(cid, SIGTTOU);
          signal(SIGCHLD, sig_handler);
         // waitpid(cid, &status, WUNTRACED);
        //  pidlst[pidnumber][0] = 0;
          printf("Cid = %d\n",cid);
          pids[pidnumber] = cid;
          strcpy(pidname[pidnumber], cpy_cmd);
          printf("pidlst = %d\n", pids[pidnumber]);
          pidnumber++;
        }
}
