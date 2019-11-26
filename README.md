# Shell 

This is a Shell developed entirely in C. 

### Installing

A step by step series of examples that tell you how to get a development env running

Copy an paste on your terminal the set of commands below.
```
git clone https://github.com/qureshinomaan/Shell.git

make 

./shell
```

# Features 

## Commands 
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
cat bello.txt > hello.txt  //Appending to hello.txt
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