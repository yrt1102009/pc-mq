#include <cstring>
#include <stdio.h>

#include "thread.h"
#include "randstr.h"

CThread::CThread() : m_tid(0), m_mq(NULL), m_isrun(false),m_isstop(false)
{
}

CThread::~CThread()
{
}

void * CThread::thread_fun(void * arg)
{
	CThread * pThread = static_cast<CThread *>(arg);
    pThread->run();
}
bool CThread::setmq(CBlockMq * mq)
{
	if(NULL == mq)
	{
		return false;
	}
	m_mq = mq;
}

bool CThread::start()
{
	return 0 == pthread_create(&m_tid, NULL, (void * (*) (void *))CThread::thread_fun, this) ;
}

bool CThread::stop()
{
	m_isstop = true;
}

bool CThread::isrun()
{
	return m_isrun;
}

bool CThread::join()
{
	pthread_join(m_tid, NULL);
}



bool CThread::run()
{
	m_isrun = true;
}

//=======================================

CProducer::CProducer()
{
}

CProducer::~CProducer()
{
}

bool CProducer::run()
{
	m_isrun = true;
	CSingleRandStr randstr;
	Data_t data;

	for(int i = 0; i < MQ_SIZE; i++)
	{
		memset(&data, 0, sizeof(data));
		randstr.getInstance().get_string(data.txt);
		m_mq->push(data);
	}
}

//========================================

CConsumer::CConsumer()
{
}

CConsumer::~CConsumer()
{
}

bool CConsumer::run()
{
	m_isrun = true;
	CSingleSort	sort;
	Data_t data;
	int count = 0;
	while(1)
	{
		if(m_isstop && 0 == m_mq->size())
		{
			break;
		}
		memset(&data, 0, sizeof(data));
		m_mq->pop(data);
//		printf("before %s \n", data.txt);
		sort.getInstance().sort_ase(data.txt);
//		printf("xxx after %s \n", data.txt);
		++count;
		if(count >= MQ_SIZE)
		{
			break;
		}
	}
}