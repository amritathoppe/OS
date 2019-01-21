Read me file:
prjct3 contains assignment submission programs.

content.h //Shared Memory datastructure
childshm.h//For child details
makefile //creates object files of master.c as omaster and worker.c as oworker
oss.c //Master Process forks and spunks the number of childs
user.c //Worker Process increments the clock
oss_log //log file of oss.c
user_log //log file of user.c

Version Control System:
RCS

Comments: Program runs good for few number of s processes and doesnt give any unexpected error messages.

Procedure to execute:
1.Type make clean
2.Type make
3.Enter ./oss -s followed by total number of spawn processes and -t followed by a number (to set alarm time) and -l followed by a string (filename)
enter in this format: ./oss -s 4 -t 2 -l out.log
