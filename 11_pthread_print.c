#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

//使用锁解决数据混乱问题
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

void*thr1(void*arg)
{
	while(1)
	{
		//先上锁
		pthread_mutex_lock(&mutex);
		printf("hello");
		sleep(rand()%3);
		printf("world\n");
		//释放锁 上锁和解锁区域叫临界区
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
}
void*thr2(void*arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("HELLO");
		sleep(rand()%3);
		printf("WORLD\n");
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
}
int main()
{
	pthread_t tid[2];
	pthread_create(&tid[0],NULL,thr1,NULL);
	pthread_create(&tid[1],NULL,thr2,NULL);

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	return 0;
}
