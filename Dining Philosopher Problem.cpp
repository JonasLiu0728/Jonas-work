#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (num_of_philosopher + 4) % N
#define RIGHT (num_of_philosopher + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };
//mutex:critical region
//S{N}:state variable
sem_t mutex;
sem_t S[N];

void test(int num_of_philosopher)
{
		if (state[num_of_philosopher] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) 
		{
			//state that eating
			state[num_of_philosopher] = EATING;
			sleep(1);
			sem_post(&S[num_of_philosopher]);
	}
}

// take up Forks
void take_fork(int num_of_philosopher)
{

	sem_wait(&mutex);
	//set to hungry
	state[num_of_philosopher] = HUNGRY;
	//eat if neighbours are not eating
	test(num_of_philosopher);
	sem_post(&mutex);
	//wait
	sem_wait(&S[num_of_philosopher]);
	sleep(1);
}


void put_fork(int num_of_philosopher)
{

	sem_wait(&mutex);

	// state that thinking
	state[num_of_philosopher] = THINKING;
	test(LEFT);
	test(RIGHT);

	sem_post(&mutex);
}

void* philosopher(void* num)
{
	int a;
	while (1) 
	{
		int *i = num;
		sleep(1);
		take_fork(*i);
		for(a=0;a<5;a++){
			if(state[a] == EATING)
				printf("E ");
			else if(state[a] == HUNGRY)
				printf("H ");
			else if(state[a] == THINKING)
				printf("T ");
		}
		printf("\n");
		sleep(0);
		put_fork(*i);
	}
}

int main()
{
	int i;
	pthread_t thread_id[N];
	// initialize the semaphores
	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++)
		sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++) {
		// create philosopher processes
		pthread_create(&thread_id[i], NULL,philosopher, &phil[i]);
	}

	for (i = 0; i < N; i++)
	{
		pthread_join(thread_id[i], NULL);//wait until thread end
	}
	return 0;
}
