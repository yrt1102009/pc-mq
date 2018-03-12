
#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

#include "singleton.h"
#include "template_mq.h"

class CThread
{
public:
	CThread();
	~CThread();
	bool setmq(CBlockMq * mq);
	bool start();
	bool stop();
	bool isrun();
	bool join();
	// thread proxy function
	static void * thread_fun(void *);
	// thread run functon, it can be overrite
	virtual	bool run();
protected:
	pthread_t m_tid;
	CBlockMq * m_mq;
	bool      m_isrun;
	bool	  m_isstop;
};

class CProducer : public CThread
{
public :
	CProducer();
	~CProducer();
	bool run();
};


class CConsumer : public CThread
{
public :
	CConsumer();
	~CConsumer();
	bool run();
};

typedef CSingleton<CProducer> CSingleProducer;
typedef CSingleton<CConsumer> CSingleConsumer;

#endif