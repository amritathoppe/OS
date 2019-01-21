#ifndef content__h
#define content__h
#include"childshm.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
struct SharedMem{
int sec;
int nanosec;
struct Childmem *shm_msg;
};
void *temp_ptr = (void *)0;
struct SharedMem *sh_mem;
#endif
