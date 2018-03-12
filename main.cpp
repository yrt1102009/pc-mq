#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "thread.h"
#include "template_mq.h"
#include "randstr.h"

pthread_mutex_t g_mutex;
pthread_cond_t g_notfull;
pthread_cond_t g_notempty;


int main(int args, char **argv)
{
	pthread_mutex_init(&g_mutex, NULL);  
    pthread_cond_init(&g_notempty, NULL);  
    pthread_cond_init(&g_notfull, NULL); 
#ifdef MULTITHREAD
	CBlockMq * mq = new CBlockMq(g_mutex, g_notfull, g_notempty);
#else
	CBlockMq * mq = new CBlockMq();
#endif

	CSingleRandStr randstr;
	randstr.getInstance();
	CSingleSort	sort;
	sort.getInstance();
	
	CSingleProducer producer;
	producer.getInstance().setmq(mq);
	CSingleConsumer consumer;
	consumer.getInstance().setmq(mq);
	
#ifdef MULTITHREAD
	
	producer.getInstance().start();
	
	consumer.getInstance().start();

	while(!producer.getInstance().isrun() || !consumer.getInstance().isrun())
	{
		sleep(1);
	}
	producer.getInstance().join();
	consumer.getInstance().stop();
	consumer.getInstance().join();
#else
	producer.getInstance().run();
	consumer.getInstance().run();
#endif

	return 0;
}