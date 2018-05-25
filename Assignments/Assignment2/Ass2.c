/*****************************************************************************************/
// Jesse Ericksen
// CSCI247
// Assignment 2

// To compile run: gcc -g Ass2.c -pthread -lrt

/* Analysis of data: 

In this assignment we created 3 threads (FIFO) which created a timer
for one, two or four seconds respectively, using signals, blocking and 
the sigwait api's. 

For more accurate data, we let each thread execute each timer 5 times while
measuring the actual time it took to receive for each thread to receive their
signal.

The difference between the expected time (1s,2s,4s) and the actual time was recorded
in the jitter column. While each individual program execution provides different results,
below is one example of a typical run:

DisplayThreadSchdAttributes:
        threadID = 0x7f37980d3700
        policy = SCHED_FIFO
        priority = 0
        startTime = Fri May 25 14:50:33 2018
        endTime = Fri May 25 14:50:33 2018
        TimeStamp [1527285033879102]
        TimeStamp [1527285034879190]   Delta [1000088]us     Jitter[88]us
        TimeStamp [1527285035879135]   Delta [999945]us     Jitter[-55]us
        TimeStamp [1527285036879140]   Delta [1000005]us     Jitter[5]us
        TimeStamp [1527285037879161]   Delta [1000021]us     Jitter[21]us
        TimeStamp [1527285038879140]   Delta [999979]us     Jitter[-21]us

DisplayThreadSchdAttributes:
        threadID = 0x7f37978d2700
        policy = SCHED_FIFO
        priority = 0
        startTime = Fri May 25 14:50:33 2018
        endTime = Fri May 25 14:50:33 2018
        TimeStamp [1527285033879172]
        TimeStamp [1527285035879187]   Delta [2000015]us     Jitter[15]us
        TimeStamp [1527285037879197]   Delta [2000010]us     Jitter[10]us
        TimeStamp [1527285039879258]   Delta [2000061]us     Jitter[61]us
        TimeStamp [1527285041879225]   Delta [1999967]us     Jitter[-33]us
        TimeStamp [1527285043879270]   Delta [2000045]us     Jitter[45]us

DisplayThreadSchdAttributes:
        threadID = 0x7f37970d1700
        policy = SCHED_FIFO
        priority = 0
        startTime = Fri May 25 14:50:33 2018
        endTime = Fri May 25 14:50:33 2018
        TimeStamp [1527285033879154]
        TimeStamp [1527285037879197]   Delta [4000043]us     Jitter[43]us
        TimeStamp [1527285041879225]   Delta [4000028]us     Jitter[28]us
        TimeStamp [1527285045879223]   Delta [3999998]us     Jitter[-2]us
        TimeStamp [1527285049879251]   Delta [4000028]us     Jitter[28]us
        TimeStamp [1527285053879220]   Delta [3999969]us     Jitter[-31]us
Main thread is exiting

___________________________________________________________________________

Above you can see the three different threads with 5 unique runs.
Through numerous trials, my data seemed to show that the jitter ranges between
-100us to 100us, but almost always falling within -50us and 50us, with a mean of 0.

The jitter did not change between threads, showing independence despite the change in
timer-period. These results agree with what I expected to see and shows how fast these
real time signals are being sent/received at this level. For instance, even the worst-case
scenario of a 100us jitter equates to just 1/10000th of a second off of expectation which 
compared to human perception, just seems extraordinary. 

*/

/*****************************************************************************************/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <inttypes.h>
#include <signal.h>
#include <errno.h>

#define	MAX_THREAD_COUNT		3

#define LOW_THREAD_PRIORITY		50

#define STACK_SIZE				0x400000
#define	MAX_TASK_COUNT			5

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)
			
/*****************************************************************************************/
pthread_mutex_t		g_DisplayMutex = PTHREAD_MUTEX_INITIALIZER;;
pthread_mutex_t 	g_SignalMutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct{
	int					threadCount;
	pthread_t			threadId;
	int					threadPolicy;
	int					threadPri;
	struct sched_param 	param;	
	long				processTime;
	int64_t				timeStamp[MAX_TASK_COUNT+1];
	time_t				startTime;
	time_t				endTime;
	int 				sig;
	sigset_t 			alarm_sig;
	int 				wakeups_missed;
	timer_t 			timer_id;
	int 				timer_Period;
    sigset_t timer_signal;	
 	int signal_number;
  	int missed_signal_count;
} ThreadArgs;

ThreadArgs g_ThreadArgs[MAX_THREAD_COUNT];

/*****************************************************************************************/

void InitThreadArgs(void){

	for(int i=0;i<MAX_THREAD_COUNT;i++) {
		g_ThreadArgs[i].threadCount = 0;
		g_ThreadArgs[i].threadId =0;
		g_ThreadArgs[i].threadPri = 0;
		g_ThreadArgs[i].processTime =0;
		
		for(int y=0; y<MAX_TASK_COUNT+1; y++){
			g_ThreadArgs[i].timeStamp[y] = 0;
		}
	}	
	
	pthread_mutex_init ( &g_DisplayMutex, NULL);
}

/*****************************************************************************************/

void DisplayThreadSchdAttributes( pthread_t threadID, int policy, int priority ){
	  
	printf("\nDisplayThreadSchdAttributes:\n        threadID = 0x%lx\n        policy = %s\n        priority = %d\n", 
		threadID,
	   (policy == SCHED_FIFO)  ? "SCHED_FIFO" :
	   (policy == SCHED_RR)	   ? "SCHED_RR" :
	   (policy == SCHED_OTHER) ? "SCHED_OTHER" :
	   "???",
	   priority);
}

/*****************************************************************************************/

void DisplayThreadArgs(ThreadArgs*	myThreadArg){

	int i,y;
	
	pthread_mutex_lock(&g_DisplayMutex);

	if(myThreadArg){
		DisplayThreadSchdAttributes(myThreadArg->threadId, myThreadArg->threadPolicy, myThreadArg->threadPri);
		printf("        startTime = %s        endTime = %s", ctime(&myThreadArg->startTime), ctime(&myThreadArg->endTime));
		printf("        TimeStamp [%"PRId64"]\n", myThreadArg->timeStamp[0] );

		for(int y=1; y<MAX_TASK_COUNT+1; y++){
			printf("        TimeStamp [%"PRId64"]   Delta [%"PRId64"]us     Jitter[%"PRId64"]us\n", myThreadArg->timeStamp[y], 
			(myThreadArg->timeStamp[y]-myThreadArg->timeStamp[y-1]),
			(myThreadArg->timeStamp[y]-myThreadArg->timeStamp[y-1]-myThreadArg->timer_Period));
		}	
	}

	pthread_mutex_unlock( &g_DisplayMutex );	
}

/*****************************************************************************************/

int CreateAndArmTimer(int unsigned period, ThreadArgs* info){

    //Create a static int variable for next signal number
    static int nextSigNum = 0;

    //Assign the next available Real-time signal to thread “signal_number”
    if(!nextSigNum){
    	nextSigNum = SIGRTMIN;
    } else {
    	nextSigNum += 1;
    }

    //Initialize the thread structure elements
    info->signal_number = nextSigNum;
    info->missed_signal_count = 0;
    info->timer_Period = period;

    //Create the signal mask corresponding to the chosen signal_number in “timer_signal”
    //Use “sigemptyset” and “sigaddset” for this
    if(sigemptyset(&info->timer_signal)){
   		printf("Error: sigemptyset\n");
   	}

    if(sigaddset(&info->timer_signal, info->signal_number)){
   		printf("Error: Adding Signal Set\n");
   	} 

    int seconds = 0;
    long nanoseconds = 0;

    //Use timer_Create to create a timer – See code in background section ****
    struct sigevent mySignalEvent;
    mySignalEvent.sigev_notify = SIGEV_SIGNAL;
    mySignalEvent.sigev_signo = info->signal_number;
    mySignalEvent.sigev_value.sival_ptr = (void *)&(info->timer_id);
    int ret = timer_create(CLOCK_MONOTONIC, &mySignalEvent, &info->timer_id);

    if(ret != 0){
    	printf("Error: Timer Create\n");
   	}

    //Arm Timer – See code in background section ****
   	struct itimerspec timerspec;
    seconds = period/1000000;
	nanoseconds = (period - (seconds * 1000000)) * 1000;
	timerspec.it_interval.tv_sec = seconds;
	timerspec.it_interval.tv_nsec = nanoseconds;
	timerspec.it_value.tv_sec = seconds;
	timerspec.it_value.tv_nsec = nanoseconds;

    ret = timer_settime(info->timer_id, 0, &timerspec, NULL);
    
    if(ret != 0){
   		printf("Error: Timer Set Time\n");
    }

    return ret;
}

/*****************************************************************************************/

static void wait_period (ThreadArgs *info){

	//Use sigwait function to wait on the timer_signal 
    sigwait(&info->timer_signal, &info->signal_number);
 
  	//Update missed_signal_count by calling "timer_getoverrun"
   	info->missed_signal_count = timer_getoverrun(info->timer_id);
}

/*****************************************************************************************/

void* threadFunction(void *arg){

	ThreadArgs*	myThreadArg;
	struct timeval	t1;
	struct timespec tms;
	int y, retVal;
  
	myThreadArg = (ThreadArgs*)arg;

	if(myThreadArg->threadId != pthread_self()){
		printf("mismatched thread Ids... exiting...\n");
		pthread_exit(arg);
	} else {
		retVal = pthread_setschedparam(pthread_self(), myThreadArg->threadPolicy, &myThreadArg->param);		//SCHED_FIFO, SCHED_RR, SCHED_OTHER
		if(retVal != 0){
			handle_error_en(retVal, "pthread_setschedparam");
		}
		myThreadArg->processTime = 0;
	}

	CreateAndArmTimer(myThreadArg->timer_Period, myThreadArg);

	//Retrieve Initial Clock Time
	myThreadArg->startTime = time(NULL);
	int p = 0;	
	clock_gettime(CLOCK_REALTIME, &tms);
	myThreadArg->timeStamp[0] = tms.tv_sec *1000000; 
	myThreadArg->timeStamp[0] += tms.tv_nsec/1000; 
	if(tms.tv_nsec % 1000 >= 500 ) myThreadArg->timeStamp[0]++; 
	
	//Waits and Checks Clock Time while < MAX_TASK_COUNT
	for(int i = 1; i <= MAX_TASK_COUNT; i++){
		wait_period(myThreadArg);
		clock_gettime(CLOCK_REALTIME, &tms);
		myThreadArg->timeStamp[i] = tms.tv_sec *1000000; 
		myThreadArg->timeStamp[i] += tms.tv_nsec/1000; 
		if(tms.tv_nsec % 1000 >= 500 ) myThreadArg->timeStamp[i]++; 
	}
	
	time_t tmp;
	tmp = time(NULL);
	myThreadArg->endTime = time(NULL);

	DisplayThreadArgs(myThreadArg);
	
	pthread_exit(NULL);
	
	return NULL;
}

/*****************************************************************************************/

int main (int argc, char *argv[]) { 

	int threadCount = 0;
    int err, i;
	int fifoPri = 60;
	int period = 1;
	int retVal;

    pthread_attr_t threadAttrib;

    sigset_t timer_signal;
    sigemptyset(&timer_signal);
    
    for(int i = SIGRTMIN; i <=SIGRTMAX; i++){
     	sigaddset(&timer_signal, i);
     	sigprocmask(SIG_BLOCK, &timer_signal, NULL);	
    }

    InitThreadArgs();

    for(int i = 0; i < MAX_THREAD_COUNT; i ++){
		g_ThreadArgs[i].threadCount = i+1;
      	g_ThreadArgs[i].threadPolicy = SCHED_FIFO;
      	g_ThreadArgs[i].param.sched_priority = fifoPri++;
	  	g_ThreadArgs[i].timer_Period = (period << i)*1000000;

      	retVal = pthread_create(&g_ThreadArgs[i].threadId, NULL, threadFunction, &g_ThreadArgs[i]);
	  	if(retVal != 0){
			handle_error_en(retVal, "pthread_create");
	  	}	    
    }

	for(int i = 0; i < MAX_THREAD_COUNT; i++){
    	pthread_join(g_ThreadArgs[i].threadId, NULL);
    }   
   
	printf("Main thread is exiting\n");
	
    return 0;	
}

/*****************************************************************************************/
