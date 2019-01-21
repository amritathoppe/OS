#ifndef childshm__h
#define childshm__h
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
struct Childmem{
int sec;
int nanosec;
int flag;
pid_t pid;
char *msg;
};
void *t_ptr = (void *)0;
#endif
