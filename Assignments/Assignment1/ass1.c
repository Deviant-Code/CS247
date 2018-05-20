#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <inttypes.h>
#include <errno.h>



//#defines

/* Explanation: 

*/

//#define MAX_THREAD_COUNT 9
#define MAX_THREAD_COUNT 9
#define MAX_TASK_COUNT   1

//Typedefs
typedef struct{
    int threadCount;
    pthread_t threadId;
    int threadPolicy;
    int threadPri;
    long processTime;
    int64_t timeStamp[MAX_TASK_COUNT+1];
    time_t startTime;
    time_t endTime;
} ThreadArgs;


//Try to change this to use a single condition variable
pthread_mutex_t g_threadMutex [MAX_THREAD_COUNT];
pthread_cond_t g_conditionVar [MAX_THREAD_COUNT];
ThreadArgs g_threadArgs[MAX_THREAD_COUNT];
int condition;


void InitGlobals(void)
{
    // Initialize thread count
    int indx;
    for (indx = 0; indx < MAX_THREAD_COUNT; indx++) {
        g_threadArgs[indx].threadCount = indx;
        //g_conditionVar[indx] = PTHREAD_COND_INITIALIZER;
        //g_threadMutex[indx] = PTHREAD_MUTEX_INITIALIZER;
        
        pthread_cond_init(&g_conditionVar[indx], NULL);
        pthread_mutex_init(&g_threadMutex[indx], NULL);
    }
    condition  = 0;

}

void DisplayThreadSchdAttributes( pthread_t threadID, int policy, int priority )
{
    printf("\nDisplayThreadSchdAttributes:\n threadID = 0x%lx\n policy = %s\n priority = %d\n", 
    threadID,
    (policy == SCHED_FIFO) ? "SCHED_FIFO" :
    (policy == SCHED_RR)? "SCHED_RR" :
    (policy == SCHED_OTHER) ? "SCHED_OTHER" :
    "???",
    priority);
}

void DisplayThreadArgs(ThreadArgs*myThreadArg)
{
    int i,y;

    if( myThreadArg )
    {
        //printf("DisplayThreadArgs: Thread Id [%lx] Pri [%d] ProcTime [%ld]\n",
        //myThreadArg->threadId, myThreadArg->threadPri, myThreadArg->processTime);

        DisplayThreadSchdAttributes(myThreadArg->threadId, myThreadArg->threadPolicy, myThreadArg->threadPri);
        printf(" startTime = %s endTime = %s", ctime(&myThreadArg->startTime), ctime(&myThreadArg->endTime));
        printf(" TimeStamp [%"PRId64"]\n", myThreadArg->timeStamp[0] );
    }
    for(y=1; y<MAX_TASK_COUNT+1; y++)
    {
        printf(" TimeStamp [%"PRId64"] Delta [%"PRId64"]us\n", myThreadArg->timeStamp[y], 
        (myThreadArg->timeStamp[y]-myThreadArg->timeStamp[y-1]));
    }
}

void DoProcess(void)
{
    unsigned int longVar =1 ;
    while(longVar < 0xffffffff) longVar++;
}

void* threadFunction(void *arg)
{
    
    ThreadArgs *myThreadArg;
    struct sched_param param;
    struct timespec    tms;
    struct timespec    tmss;
    int y = 0;
    
//1. Typecast the argument to a “ThreadArgs*” variable
    myThreadArg = (ThreadArgs*) arg;
   
//2. Use the “pthread_setscheduleparam” API to set the thread policy
    int status;
    status = pthread_setschedparam(pthread_self(), myThreadArg->threadPolicy, &param);
    if(status!=0){
        if(status==EPERM){
            fprintf(stderr,"EPERM\n");
        } else if(status==EINVAL) {
            fprintf(stderr,"EINVAL\n");
        } else {
            fprintf(stderr,"neither EPERM nor EINVAL\n");
        }
        fprintf(stderr,"error %d\n",status);
        errno=status;
        exit(1);
    }

   //if (s!=0) {
     //   //handle_error_en(s, "pthread_setschedparam");
       // fprintf(stderr, "%d\n", myThreadArg->threadPolicy);
        //fprintf(stderr, "ERROR: %d:%s, pthread_setschedparam\n", s,strerror(s));
        //return myThreadArg;
   // }
        
//3. Init the Condition variable and associated mutex
    
//4. Wait on condition variable
    pthread_mutex_lock(&g_threadMutex[myThreadArg->threadCount]);
    condition = 1;
    while(condition == 0)
        pthread_cond_wait(&g_conditionVar[myThreadArg->threadCount],&g_threadMutex[myThreadArg->threadCount]);
        pthread_mutex_unlock(&g_threadMutex[myThreadArg->threadCount]);

//5. Once condition variable is signaled, use the “time” function and the “clock_gettime(CLOCK_REALTIME, &tms)” to get timestamp
    clock_gettime(CLOCK_REALTIME, &tms);
    myThreadArg->timeStamp[y] = tms.tv_sec*1000000;
    myThreadArg->timeStamp[y]+=tms.tv_nsec/1000;
    if(tms.tv_nsec %1000 >= 500)
        myThreadArg->timeStamp[y+1]++;
        myThreadArg->startTime = tms.tv_sec + tms.tv_nsec;

//6. Call “DoProcess” to run your task
    DoProcess();
    condition = 0;

//7. Use “time” and “clock_gettime” to find end time.
    clock_gettime(CLOCK_REALTIME, &tmss);
    myThreadArg->timeStamp[y+1] = tms.tv_sec*1000000;
    myThreadArg->timeStamp[y+1]+=tms.tv_nsec/1000;
    if(tms.tv_nsec %1000 >= 500)
        myThreadArg->timeStamp[y+1]++;
        myThreadArg->endTime = tmss.tv_sec + tmss.tv_nsec;

//8. You can repeat steps 6 and 7 a few times if you wish
    return 0;
}

int main (int argc, char *argv[]) 
{
    
//1. Initialize Globals
    int index;
	InitGlobals();
    
//2. Create a number of threads (start with 1 and increase to 9) using “pthread_Create”
    for (index = 0; index < MAX_THREAD_COUNT; index++) {
        pthread_create(&g_threadArgs[index].threadId, NULL, *threadFunction, &g_threadArgs[index].threadCount);
    }
//3. Assign 3 threads to SCHED_OTHER, another 3 to SCHED_FIFO and another 3 to SCHED_RR
    for(index = 0; index < MAX_THREAD_COUNT;index++) {
        if (index % 3 == 0) {
             g_threadArgs[index].threadPolicy = SCHED_FIFO;
        } else if (index % 3 == 1) {
             g_threadArgs[index].threadPolicy = SCHED_OTHER;
        } else {
             g_threadArgs[index].threadPolicy = SCHED_RR;
        }

    }
//4. Signal the condition variable
   pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
//5. Call “pthread_join” to wait on the thread
    for(index = 0; index < MAX_THREAD_COUNT; index++) {
        pthread_join(g_threadArgs[index].threadId, NULL);
    //6. Display the stats on the threads
        DisplayThreadArgs(&g_threadArgs[index]);
    }
}
