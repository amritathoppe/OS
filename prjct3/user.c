#include "content.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#define skey 877077
#define BUFF_SZ sizeof (struct SharedMem)
#define ckey 877088
#define CHBUFF_SZ sizeof(struct Childmem)

sem_t *babu;
sem_t *dummy;
int main(int argc,char* argv[])
{
int shmid,i,childmsgid;
char * filename=argv[1];
char* semname=argv[2];
FILE *op_file;
if((op_file=fopen(filename,"w+"))==NULL)
{
perror("\n OSS :fopen failure Give -l filename");
}
shmid=shmget(skey, BUFF_SZ, 0666);
if(shmid <0)
{
        perror("shmget");
        exit(1);
}
        temp_ptr = ( shmat ( shmid, 0, 0 ) );
        sh_mem = ( struct SharedMem * )( temp_ptr );
        childmsgid=shmget(ckey, CHBUFF_SZ, 0666);
        if(childmsgid <0)
        {
        perror("shmget");
        exit(1);
        }
        t_ptr = ( shmat ( childmsgid, 0, 0 ) );
        sh_mem->shm_msg = ( struct Childmem * )( t_ptr );
        sh_mem->shm_msg->sec=sh_mem->sec;
        sh_mem->shm_msg->nanosec=sh_mem->nanosec+1;
        dummy=sem_open(semname,0);
        if(!dummy )
        {
        int err = errno;
        printf("Error message:%s\n",strerror(err));
        return err;
        }
        int value;
        sem_getvalue(dummy,&value);
while(1){
        int e=0;
        if((sem_wait(dummy))==0){
        printf("\n Locked by: %d\n",getpid());
        sem_getvalue(dummy,&value);
        }
        else
        {
        e= errno;
        printf("Error number:%d\n",e);
        }
        if((sh_mem->sec > sh_mem->shm_msg->sec))
        {
        printf("Exceeded the time\n");
        sh_mem->shm_msg->pid=getpid();
        sh_mem->shm_msg->flag=1;
        printf("OSS:%d is terminating at my time %d.%d because it reached %d.%d in user",sh_mem->shm_msg->pid,sh_mem->sec,sh_mem->nanosec,sh_mem->shm_msg->sec,sh_mem->shm_msg->nanosec);
        fprintf(op_file,"OSS:%d is terminating at my time %d.%d because it reached %d.%d in user",sh_mem->shm_msg->pid,sh_mem->sec,sh_mem->nanosec,sh_mem->shm_msg->sec,sh_mem->shm_msg->nanosec);
        sem_post(dummy);
        break;
        }
        sem_post(dummy);
        }
        sem_getvalue(dummy,&value);
 }
