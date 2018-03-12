#ifndef __LOCK_H__
#define __LOCK_H__

#include <pthread.h>


class CLock
{
private:
	CLock(CLock & src) : m_mutex(src.m_mutex)
	{
	}

	CLock& operator=(CLock &rhs)
	{
	}
public :
	CLock(pthread_mutex_t & mutex) : m_mutex(mutex)
	{
		pthread_mutex_lock(&m_mutex);
	}

	~CLock()
	{
		 pthread_mutex_unlock(&m_mutex);
	}

private:
	pthread_mutex_t & m_mutex;
};

#endif