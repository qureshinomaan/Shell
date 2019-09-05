#define _POSIX_SOURCE
#include <termios.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>

// int main() {
//   pid_t pid;
//   int status;

//   if (fork() == 0)
//     if ((pid = tcgetpgrp(STDOUT_FILENO)) < 0)
//       perror("tcgetpgrp() error");
//     else {
//       printf("original foreground process group id of stdout was %d\n",
//              (int) pid);
//       if (setpgid(getpid(), 0) != 0)
//         perror("setpgid() error");
//       else {
//         printf("now setting to %d\n", (int) getpid());
//         if (tcsetpgrp(STDOUT_FILENO, getpid()) != 0)
//           perror("tcsetpgrp() error");
//         else if ((pid = tcgetpgrp(STDOUT_FILENO)) < 0)
//           perror("tcgetpgrp() error");
//         else
//           printf("new foreground process group id of stdout was %d\n",
//                  (int) pid);
//       }
//     }

//   else wait(&status);
// }