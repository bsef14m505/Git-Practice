#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int ans = 0;

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void * funct1(void* arr)
{
	int i = 0;
	int *arr1 = arr;
	for (i = 0; i<100; i++)
	{
		arr1[i] = i + 1;
	}
	pthread_exit(NULL);
}

void * funct2(void* arr)
{
	int i = 1;
	int *arr1 = arr;

	for (i; i<100; i = i + 2)
	{
		pthread_mutex_lock(&mut);
		ans += arr1[i];
		pthread_mutex_unlock(&mut);
	}

	pthread_exit(NULL);
}

void * funct3(void* arr)
{
	int i = 0;
	int *arr1 = arr;
	for (i; i<100; i = i + 2)
	{
		pthread_mutex_lock(&mut);
		ans -= arr1[i];
		pthread_mutex_unlock(&mut);
	}
	pthread_exit(NULL);
}

void * funct4()
{
	printf("\n\nAnswer= %d", ans);
	pthread_exit(NULL);
}

void main()
{
	int arr[100];
	pthread_t t1, t2, t3, t4;
	pthread_create(&t1, NULL, funct1, (void*) &arr);
	pthread_join(t1, NULL);
	int i;
	printf("Array Values:\n");
	for (i = 0; i<100; i++)
	{
		printf("%d ", arr[i]);
	}
	pthread_create(&t2, NULL, funct2, (void*) arr);
	pthread_create(&t3, NULL, funct3, (void*) arr);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_create(&t4, NULL, funct4, NULL);
	pthread_join(t4, NULL);
	pthread_mutex_destroy(&mut);
}