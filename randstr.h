#ifndef __RANDSTR_H__
#define __RANDSTR_H__

#include <pthread.h>

#include "singleton.h"

class CRandStr
{
public:
	bool get_string(char * output);
};


class CSort
{
public:
	bool sort_ase(char * inoutput);
};


typedef CSingleton<CRandStr> CSingleRandStr;
typedef CSingleton<CSort> CSingleSort;

#endif


































