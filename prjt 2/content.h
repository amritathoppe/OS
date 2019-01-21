#ifndef content__h
#define content__h
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
struct SharedMem{
int sec;
int millisec;
};
int smem_id;
void *temp_ptr = (void *)0;
struct SharedMem *sh_mem;
#endif
