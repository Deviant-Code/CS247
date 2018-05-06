#include <stdio.h>
#include <pthread.h>

#define NUMTHRDS 2

pthread_t t[NUMTHRDS];
int coin_flip;


static void *thread2(void *_){
	printf("Thread 2: flipped coin %d\n", coin_flip);
}


static void * thread1(void * _)
{
	printf("Thread 1: flipped coin %d\n", coin_flip);

}

int main()
{
	pthread_create(&t[1], NULL, thread2, NULL);
	pthread_create(&t[0], NULL, thread1, NULL);

	pthread_exit(NULL);


	return 1;
}
