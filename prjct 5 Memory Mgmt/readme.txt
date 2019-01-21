Read me file:
prjct.5 contains assignment submission programs.

res.h //Shared Memory Timer, Resource Descriptor datastructure
makefile //creates object files of oss.c as oss and user.c as user
oss.c //Creates,Schedules Process, Runs Banker Saftey Algm,Manages Deadlock,Blocks/Unblocks the deadlocked process
user.c //executes the process,manages the request release allocated resource calculations
oss_log //log file of oss.c
user_log //log file of user.c
oss.c,v
user.c,v
output.out //default output file

Version Control System:
RCS

Comments: Program runs good,At times no deadlock happens if so retry again with ./oss -s 5 -v

Options:
-h :displays options
-s :sets the spawn children; Eg: ./oss -s 5
-v :sets the verbose Eg: ./oss -v
-l :sets the log file Eg: ./oss -l outmsg.out

Procedure to execute:
1.Type make
2.Enter ./oss followed by options
Sample worked ones are:
./oss -s 4

./oss -s 5 -v

./oss -s 5 -v -l msglog.out

4.type vi output.out (Default output file) to view the generated output

Generated output when verbose not set
contains deadlock detection algm,deadlock, blocked and unblocked details
when verbose set using -v
in addition to the above it prints resource grant, release details and the resource allocation table once per 20 resources grants
