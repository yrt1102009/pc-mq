#ifndef __SINGLETON_H__
#define __SINGLETON_H__


template<typename T>
class CSingleton
{
public:  
    CSingleton(){}
	CSingleton(const CSingleton & rhs){}
	CSingleton& operator=(const CSingleton &rhs){}
	~CSingleton(){}
public:
	static T& getInstance()  
    {
		if(NULL == m_Instance)
        {
                m_Instance=new T();
        }
        return *m_Instance;  
    }  
public:
    static T * m_Instance; 
};

template<typename T> T * CSingleton<T>::m_Instance=NULL;

#endif