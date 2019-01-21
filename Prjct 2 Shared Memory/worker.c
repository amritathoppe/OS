#include "content.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define skey 877077
#define BUFF_SZ sizeof (struct SharedMem)
int main(int argc,char* argv[])
{
        int shmid,i;
        int s=atoi(argv[1]);
        int x=s*1000000;
        shmid=shmget(skey, BUFF_SZ, 0666);
        if(shmid <0)
                {
                perror("shmget");
                exit(1);
                }
        temp_ptr = ( shmat ( shmid, 0, 0 ) );
        sh_mem = ( struct SharedMem * )( temp_ptr );
        for(i=1;i<=x;i++)
        {
        sh_mem->millisec = sh_mem->millisec + 1;
        if(sh_mem->millisec >= 999)//tracks overflow
        {
        sh_mem->sec=sh_mem->sec+1;
        sh_mem->millisec=0;
        }
        }
        shmdt(temp_ptr);
}
