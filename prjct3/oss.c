#include"content.h"
#include"childshm.h"
#include<semaphore.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<signal.h>
#include<errno.h>
#define skey 877077
#define ckey 877088
#define BUFF_SZ sizeof (struct SharedMem)
#define CHBUFF_SZ sizeof (struct Childmem)
int shmid;int childshmid;
void cleaning(int);
sem_t *babu;//Semaphore mutex
sem_t *dummy;
char *Semname="babu376";
int arr[10];//to hold pids
int miss=0;//to ck clk increments
int n;//to chk if it can access sh_mem
FILE *output_file;
char *outfile="output.log";
char *filename;
void Increment_Clk()
{
sh_mem->nanosec+=1;

if(sh_mem->nanosec >= 999999999)
{
sh_mem->sec=sh_mem->sec+1;
sh_mem->nanosec=0;
miss++;
}

}
void Chk_Flag();
void kill_child(int sig)
{
int i;
printf("Kill child called..\n");
for(i=0;i<1;i++)
{
kill(arr[i],SIGTERM);
}
printf("\n Killed All children");
}
void signal_handler_func(int signum)
{
        signal(SIGINT,signal_handler_func);
        printf("\n Ctrl + c is pressed\n");
        signal(SIGINT,kill_child);
        fprintf(stderr,"\n Shared Memory content Seconds:%d Nanoseconds:%d\n",sh_mem->sec,sh_mem->nanosec);
        cleaning(shmid);
        exit(0);
}
void signal_alarm(int signum)
{
        signal(SIGALRM,signal_alarm);
        printf("\n Alarm  is called  \n");
        sem_unlink(Semname);
        cleaning(shmid);
        exit(0);
}
int main(int argc,char* argv[])
{
int s,t,i,choice;
pid_t childpid=0;
char *Path="./ouser";
n=0;
t=2;//by default
s=5;//by default
while((choice=getopt(argc,argv,"tlhs:"))!=-1)
{
switch(choice)
{
        case 's': s = atoi(argv[2]);break;
        case 'h':fprintf(stderr,"Enter -s followed by number to spawn processes \n Enter -h to display help message\nEnter -l to generate log file \n Enter -t to enter time\n");return 0;
        case 'l':fprintf(stderr,"%s:Log file",argv[0]);
                outfile=argv[6];//for fopen
                filename=argv[6];//for exec argument
                printf("%s\n",outfile);
        break;
        case 't':printf("Time to terminate");
        t=atoi(argv[4]);
        printf("%d",t);
        break;
        default:return 0;}
}
if((output_file=fopen(outfile,"w+"))==NULL)
        {
        perror("\n OSS :fopen failure...sending kill signals");
        }
else printf("Fopen successfull\n");
signal(SIGINT,signal_handler_func);
signal(SIGALRM,signal_alarm);
signal(SIGINT,kill_child);
alarm(t);
shmid=shmget(skey,BUFF_SZ,IPC_CREAT|0666);
childshmid=shmget(ckey,CHBUFF_SZ,IPC_CREAT|0666);
if(shmid <0)
{
        int err=errno;
        printf("Error %s",strerror(err));
        exit(1);
}
temp_ptr =shmat (shmid, 0, 0);
sh_mem = (struct SharedMem *) temp_ptr;
sh_mem->sec=0;
sh_mem->nanosec=0;
if(childshmid<0)
{
int err=errno;
printf("Error %s",strerror(err));
exit(1);
}
t_ptr=shmat(childshmid,0,0);
sh_mem->shm_msg=(struct Childmem *) t_ptr;
sh_mem->shm_msg->flag=0;
dummy=sem_open(Semname,O_CREAT, 0666, 1);
if(!dummy )
{
        int err = errno;
        return err;
}
int value;
sem_getvalue(dummy,&value);
sh_mem->sec+=2000;
int j,count=0;
for(j=0;j<1;j++)//Run for s processes at a time
{
        childpid=fork();
        arr[j]=childpid;
        count=count+1;
        if (childpid == 0)
        {
        execlp(Path,Path,filename,Semname,(char*)NULL);
        }
}

while(1)
{
        Increment_Clk();

        Chk_Flag();
}
        sem_unlink(Semname);
        while(wait(NULL)>0);
        cleaning(shmid);
        return 0;
}
void cleaning(int shmid)
{       shmdt(t_ptr);
        shmdt(temp_ptr);
        shmctl(shmid,IPC_RMID,NULL);
        exit(0);
}
void Chk_Flag()
{
      if(sh_mem->shm_msg->flag == 1 )
             {
                      int x=sh_mem->shm_msg->flag;
                               if(x==1)
                                       {
                                                sh_mem->shm_msg->flag=0;
                                                         printf("Child Terminated %d\n",sh_mem->shm_msg->pid);
                                                                  }
                                                                           }
      wait(NULL);
              childpid=fork();
                      count=count+1;
                              if(childpid==0)
                               {
                               printf("Entered..");
                                execlp(Path,Path,argv[2],Semname,(char*)NULL);
                                }
                               
}
