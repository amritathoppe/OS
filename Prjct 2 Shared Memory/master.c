#include "content.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<signal.h>
#define skey 877077
#define BUFF_SZ sizeof (struct SharedMem)
int shmid;
void cleaning();
void signal_handler_func(int signum)
{
        signal(SIGINT,signal_handler_func);
        printf("\n Ctrl + c is pressed\n");
        fprintf(stderr,"\n Shared Memory content Seconds:%d Milliseconds:%d",sh_mem->sec,sh_mem->millisec);
        cleaning(shmid);
        exit(0);
}
void signal_alarm(int signum)
{
        signal(SIGALRM,signal_alarm);
        printf("\n Alarm  is called\n");
        cleaning(shmid);
        exit(0);
}
int main(int argc,char* argv[])
{
        int n,choice;
        int s;
        int pid,j;
        char *Path="./oworker";
        while((choice=getopt(argc,argv,"hsn:"))!=-1)
        {
        switch(choice)
        {
                case 'n':
                        n=atoi(argv[2]);
                        break;
                case 's':
                        s=atoi(argv[4]);
                        break;
                case 'h':
                        fprintf(stderr,"enter -n for total process;enter -s for spawn process;enter -h for alarm");
                        return 0;
                default:
                        fprintf(stderr,"enter properly");
                        return 0;
        }
      }

        shmid=shmget(skey, BUFF_SZ, IPC_CREAT|0666);
        if(shmid <0)
        {
                perror("shmget");
                exit(1);
        }
        temp_ptr =  shmat ( shmid, 0, 0 ) ;
        sh_mem = (struct SharedMem * ) temp_ptr;
        sh_mem->sec=0;
        sh_mem->millisec=0;
        signal(SIGINT,signal_handler_func);
        signal(SIGALRM,signal_alarm);
        int count=0;
        alarm(2);
        for(j=0;j<s;j++)
        {
                pid=fork();

                if(pid==0)
                {
                count++;
                execlp(Path,Path,argv[2],(char*)NULL);
                }
        }

        do
        {
                wait(NULL);
                pid=fork();
                count++;
                if(pid==0)
                {
                execlp(Path,Path,argv[2],(char*)NULL);
                }
        }while(count<n);
        while(wait(NULL)>0);
        fprintf(stderr,"\n Shared Memory content Seconds:%d Milliseconds:%d",sh_mem->sec,sh_mem->millisec);

        cleaning(shmid);
        return 0;
}
void cleaning(int shmid)
{
        shmdt(temp_ptr);
        shmctl(shmid,IPC_RMID,NULL);
        exit(0);
}
