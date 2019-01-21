#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main (int argc, char *argv[]) {
pid_t childpid = 0;
int i, n,choice;
while((choice=getopt(argc,argv,"phn:"))!=-1)
{
switch(choice)
{
case 'n': n = atoi(argv[2]);break;
case 'h':fprintf(stderr,"Enter -n followed by number to generate processes\nEnter -h to display help message\nEnter -p to generate test error message");return 0;
case 'p':fprintf(stderr,"%s:",argv[0]);
perror(("Error"));return 0;
default:return 0;}
}
 for (i = 1; i < n; i++)
 if (childpid = fork())
 break;
 fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",i, (long)getpid(), (long)getppid(), (long)childpid);
 return 0;
}
