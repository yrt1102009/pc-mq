#ifndef __TEMPLATE_MQ_H__
#define __TEMPLATE_MQ_H__


#include <pthread.h>
#include <queue>

#include "lock.h"
#include "data.h"

const unsigned int MQ_SIZE = 4096;

template <class T>
class CMq
{
	public :
		CMq()
		{
		}
#ifdef MULTITHREAD
		CMq( pthread_mutex_t & mutex, pthread_cond_t & notfull, pthread_cond_t & notempty)	
			:	 m_mutex(mutex), m_notfull(notfull), m_notempty(notempty)
		{
		}
#endif
		~CMq()
		{
			clear();
		}

	public:
		bool push(T & data)
		{
#ifdef MULTITHREAD
			CLock lock(m_mutex);
			while(MQ_SIZE <= m_queue.size())
			{
				pthread_cond_wait(&m_notfull, &m_mutex);//wait queue is not full
			}
			m_queue.push(data);
			pthread_cond_signal(&m_notempty);//notify queue has data;
#else
			m_queue.push(data);
#endif
			return true;
		}
		//it will overwrite input para
		bool pop(T & data)
		{
#ifdef MULTITHREAD
			CLock lock(m_mutex);
			while(m_queue.empty())
			{
				pthread_cond_wait(&m_notempty, &m_mutex);//wait queue is not full
			}

			data = m_queue.front();
			m_queue.pop();
			pthread_cond_signal(&m_notfull);//notify queue has space save data;
#else
			data = m_queue.front();
			m_queue.pop();
#endif
			return true;
		}
		int size()
		{
#ifdef MULTITHREAD
			CLock lock(m_mutex);
#endif
			return m_queue.size();
		}
		void clear()
		{
#ifdef MULTITHREAD
			CLock lock(m_mutex);
#endif
			while (!m_queue.empty())
			{
				m_queue.pop();
			}
		}

	private:
		std::queue<T> m_queue;
#ifdef MULTITHREAD
		pthread_mutex_t &  m_mutex;
		pthread_cond_t & m_notfull;	//queue is full and wait until not full go on 
		pthread_cond_t & m_notempty;	//queue is empty and wait until not empty go on
#endif
};


typedef CMq <Data_t>  CBlockMq;

#endif
