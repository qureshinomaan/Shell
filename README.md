# Shell 

This is a Shell developed entirely in C. The shell emulates the normal bash in linux systems. It is able to handle bakground processes, foreground processes, input-output redirection, command redirection etc. 

### Installing

A step by step series of examples that tell you how to get a development env running

Copy an paste on your terminal the set of commands below.
```
git clone https://github.com/qureshinomaan/Shell.git

make 

./shell
```

# Features 

##Display 
* The format is <username@system_name:curr_dir>
* ~ signifies the address of Home Directory.  

## Commands 

### pwd 
* Prints the path present working directory. 

### cd <directory path>
* cd changes the pwd to the specified directory path. 

### ls [al]
* lists all the file in the pwd. 

### pinfo
* Prints the process related info of Shell program. 

### pinfo <pid>
* prints the process info about given pid. 

### history 
* Tells the last 10 commands executed on shell. 

### history <n>
* Prints the last 'n' commands. 
* 'n' is specified by user. 

### All Other General shell commands. 
* All other commands like cat, grep, etc. can be executed through the shell. 
* The difference is that they are builtin and ls, pwd, cd were built by me. 

### setenv var [value] :
* If the enviroment variable does not exist, then creates it.
* Modifies the existing value if the environment variable already exists. 

### unsetenv var 
* Destroys the evironment variable if exists. 

### jobs 
* prints all the currently running jobs along with their pids. 

### kjob <jobnumber> <signalNumber>
* Takes the job number of the process and sends the signal specified by signalNumber to it. 

### fg <jobNumber> 
* Brings the job running in background to the foreground. 

### bg <jobNumber>
* Changes a stopped background job to a running background job. 

### overkill 
* Kills all background process at once. 

### quit 
* Exits the shell. 

### CTRL-Z 
* Changes teh currently running job to stop, and pushes it to background process.

### CTRL-C
* Sends a SIGINT signal to the current forground job of this shell. 
* If there is no foreground process currently this should have no effect. 


### Foreground Processes
* Just type the command's name you want to run. 
* These processes have the access of input and output on the terminal window.
* Example 
```
vim bello;ls;
```
### Background Processes
* Type the command's name you want to execute. End it with a &.
* These processes run in the background meaning they do not have input and output accesses from the terminal window.
* Example
```
vim bello &
```

## Input/Output Redirection.
* Input Redirection 
```
sort < lines.txt
```

* Output Redirection 
```
cat bello.txt > hello.txt  //Overwriting hello.txt
cat bello.txt >> hello.txt  //Appending to hello.txt
```

* Input-Output Redirection 
```
sort < lines.txt > output.txt 
```

## Command Redirection Using Pipes
* A pipe is a basically a channel of communication between two processes. 
* Identified by '|'
* Example 
```
cat bello.txt | grep hello
ls | grep *.txt > out.txt 
```


# Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

# Authors

* **Nomaan Qureshi** - *Initial work*


# Acknowledgments

* CSE-1 Course TA's.
* Professor P.K. Reddy, IIIT Hyderabad.