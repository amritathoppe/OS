#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <pthread.h>


#define MAX_CHILD 18
#define QUANTUM 20 // specified interms of micro seconds ie.2 milliseconds
#define MAX_CPU_TIME 80 // specified interms of micro seconds ie.8 milliseconds
#define TOTAL_QUEUE 2
#define TERMINATE_PROCESS 0
#define TERMINATE_AT_QUANTUM 1
#define WAIT_FOR_EVENT 2
#define PREEMPT 3
#define CHILD_EXE "./user"

#define RUN_TIME_SECONDS 10

FILE *output_file;
const char *outfile = "output.log";
struct timespec mainStartTime;



typedef struct {
        pid_t pid;
        int total_cpu_time;
        int total_system_time;
        int last_burst_time;
        int total_wait_time;
        int process_priority;
        int quantum;
        int process_index;
        int process_criteria; //0 -> terminates; 1 -> terminates at quantum time; 2 -> wait for event; 3 -> pre-mpt
        char state[20];
} PCB;


void initialise_rand() {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        srand((time_t)ts.tv_nsec);

        clock_gettime(CLOCK_MONOTONIC, &mainStartTime);
}
int uniform_distribution(int rangeLow, int rangeHigh) {
        double myRand = rand()/(1.0 + RAND_MAX);
        int range = rangeHigh - rangeLow + 1;
        int myRand_scaled = (myRand * range) + rangeLow;
        return myRand_scaled;
}

int get_file_descriptor(size_t size, int index) {
        char file_name[50];
                memset(file_name, '\0', sizeof(file_name));
        sprintf(file_name, "memory_%d", index);
        int memFd = shm_open(file_name, O_RDWR | O_CREAT, S_IRWXU );
        if (memFd == -1)
        {
                perror("Can't open file");
                return -1;
        }

        int res = ftruncate(memFd, size);
        if (res == -1)
        {
                perror("Can't truncate file");
                return -1;
        }

        return memFd;
}

void *get_shared_memory(size_t size, int index, int memFd) {
        if(memFd == -1) {
                memFd = get_file_descriptor(size, index);
        }

        void *buffer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0);
        if (buffer == NULL)
        {
                perror("Can't mmap");
                return NULL;
        }

        return buffer;
}
void* create_shared_memory(size_t size, int index) {
        int memFd = get_file_descriptor(size, index);

        void *buffer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0);
        if (buffer == NULL)
        {
                perror("Can't mmap");
                return NULL;
        }

        return buffer;
}


void write_log(char *log)
{
        if(output_file == NULL)
        {
                if((output_file=fopen(outfile,"w+"))==NULL)
                {
                        perror("\n OSS :fopen failure...sending kill signals");
                }
                else printf("Fopen successfull\n");
        }

        if(output_file != NULL){

                fprintf(output_file, log);
                fprintf(output_file, "\n");
                fflush(output_file);
        }
}

long long current_timestamp() {
        struct timespec te;
        clock_gettime(CLOCK_MONOTONIC, &te);
        long long milliseconds = (te.tv_nsec - mainStartTime.tv_nsec);
        return milliseconds;
}
