Read me file:
kuppubab.6 contains assignment submission programs.

header.h //Shared Memory,Page Table,Frame Table datastructure
makefile //creates object files of oss.c as oss and user.c as user
oss.c //Oss Process forks and spunks the number of childs,services the user requests using paging and frametables,manages page fault,alarm enabled,cleans up.
user.c //User Process requests the read/write access to the oss
oss6_log //log file of oss.c
user6_log //log file of user.c

Version Control System:
RCS

Comments: Program runs good without any errors, output is generated in output.log file

Procedure to execute:
1.Type make clean
2.Type make
3.Enter ./oss 4
Where 4 is the no of max child to be spawned.
~
