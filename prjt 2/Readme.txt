Read me file:
kuppubab.2 contains assignment submission programs.

content.h //Shared Memory datastructure
makefile //creates object files of master.c as omaster and worker.c as oworker
master.c //Master Process forks and spunks the number of childs
worker.c //Worker Process increments the clock
masterlog //log file of master.c
workerlog //log file of worker.c

Version Control System:
RCS

Comments: All program runs good doesnt give any unexpected error messages.

Procedure to execute:
1.Type make
2.Enter ./omaster -n followed by total number of processes and -s followed by a number (to limit the
no of processes run at a time)
Sample : ./omaster -n 4 -s 2

