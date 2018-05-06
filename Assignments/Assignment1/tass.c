#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <inttypes.h>

//#defines

#define MAX_THREAD_COUNT 9

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

//Globals 
ThreadArgs threads[];


//Try to change this to use a single condition variable
pthread_mutex_t g_ThreadMutex [MAX_THREAD_COUNT];
pthread_cond_t g_conditionVar [MAX_THREAD_COUNT];
ThreadArgs g_ThreadArgs[MAX_THREAD_COUNT];


void InitGlobals(void)
{
// Initialize all globals
	ThreadArgs threads[MAX_THREAD_COUNT];

}

void DisplayThreadSchdAttributes( void )
{
int policy;
struct sched_param param;

pthread_getschedparam(pthread_self(), &policy, &param);

printf("DisplayThreadSchdAttributes:\n threadID = 0x%lx\n policy = %s\n priority = %d\n", 
pthread_self(),
(policy == SCHED_FIFO) ? "SCHED_FIFO" :
(policy == SCHED_RR) ? "SCHED_RR" :
(policy == SCHED_OTHER) ? "SCHED_OTHER" :
"???",
param.sched_priority);
}

void DisplayThreadStats(ThreadArgs* myThreadArg)
{
if( myThreadArg )
{
//printf("DisplayThreadArgs: Thread Id [%lx] Pri [%d] ProcTime [%ld]\n",
// myThreadArg->threadId, myThreadArg->threadPri, myThreadArg->processTime);

DisplayThreadSchdAttributes();
printf(" startTime = %s\n endTime = %s\n", ctime(&myThreadArg->startTime), ctime(&myThreadArg->endTime));
printf(" TimeStamp [%"PRId64"]\n", myThreadArg->timeStamp[0] );

for(int y=1; y<MAX_TASK_COUNT+1; y++)
{
printf(" TimeStamp [%"PRId64"] Delta [%"PRId64"]us\n", myThreadArg->timeStamp[y], 
(myThreadArg->timeStamp[y]-myThreadArg->timeStamp[y-1]));
} 

}
else
{

for(int i=0;i<MAX_THREAD_COUNT;i++)
{
//printf("DisplayThreadArgs: Thread Id [%lx] Pri [%d] ProcTime [%ld]\n",
// g_ThreadArgs[i].threadId, g_ThreadArgs[i].threadPri, g_ThreadArgs[i].processTime);

DisplayThreadSchdAttributes();
printf(" TimeStamp (task starting) [%ld]\n", g_ThreadArgs[i].timeStamp[0] );

for(int y=1; y<MAX_TASK_COUNT+1; y++)
{
printf(" TimeStamp (task completed) [%ld] Delta [%ld]\n", g_ThreadArgs[i].timeStamp[y], 
(g_ThreadArgs[i].timeStamp[y]-g_ThreadArgs[i].timeStamp[y-1]));
} 
}
} 
}

void DoProcess(void)
{
unsigned int longVar =1 ;

while(longVar < 0xffffffff) longVar++;
}



void* threadFunction(void *arg)
{
/*
1. Typecast the argument to a “ThreadArgs*” variable
2. Use the “pthread_setscheduleparam” API to set the thread policy
3. Init the Condition variable and associated mutex
4. Wait on condition variable
5. Once condition variable is signaled, use the “time” function and the “clock_gettime(CLOCK_REALTIME, &tms)” to get timestamp
6. Call “DoProcess” to run your task
7. Use “time” and “clock_gettime” to find end time.
8. You can repeat steps 6 and 7 a few times if you wish
*/
}

int main (int argc, char *argv[]) 
{
	initglobals();
	int index;
	/* Initialize threads. */ 
	for(index = 0; index < MAX_THREAD_COUNT; index++){
		pthread_create(&threads[index].threadId,NULL,threadFunction, NULL);
		/* Set scheduling priority of threads */
		if(index % 3 == 0){
			pthread_attr_setschedpolicy(&threads[index].threadId, SCHED_FIFO);
		} else if(index % 3 == 1){
			pthread_attr_setschedpolicy(&threads[index].threadId, SCHED_OTHER;
		} else {
			pthread_attr_setschedpolicy(&threads[index].threadId, SCHED_RR);
		}
		pthread_cond_signal(&g_conditionVar[index]);
		pthread_join(&threads[index].threadId, NULL);
		DisplayThreadSchdAttributes(&ThreadArgs[index]);
	}
}
}
