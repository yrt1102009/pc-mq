
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <assert.h>
#include <string.h>

#include "randstr.h"

static const char *  character_str[] = {"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM", "1234567890"};
const unsigned char RAND_SIZE = 12;



bool CRandStr::get_string(char * output)
{
	const int arr_size = sizeof(character_str)/sizeof(character_str[0]);
	unsigned char * character_len_arr = new unsigned char[arr_size];
	int outputlen=0;
	for(int i = 0; i <arr_size; i++)
	{
		int strSize = strlen(character_str[i]);
		character_len_arr[i] = strSize;
		srand((int)time(0));
		int pos = rand()%strSize;
		output[outputlen++] = character_str[i][pos];
	}
    for(int x=0; x<RAND_SIZE-arr_size; x++)
	{
		srand((int)time(0));
		int index = rand()%arr_size;
		srand((int)time(0));
		int pos = rand()%character_len_arr[index];
		output[outputlen++] = character_str[index][pos];
	}
	output[outputlen++] = '\0';
	delete [] character_len_arr;
	return true;

}

bool CSort::sort_ase(char * inoutput)
{
	int size = strlen(inoutput);
	for(int i = 0; i < size - 1; i++)
	{
		int minpos = i;
		for(int k = i+1; k < size; k++)
		{
			if( inoutput[k] < inoutput[minpos])
			{
				minpos = k;
			}
		}
		if ( minpos != i )
		{
			inoutput[i] = inoutput[i] ^ inoutput[minpos];
			inoutput[minpos] = inoutput[i] ^ inoutput[minpos];
			inoutput[i] = inoutput[i] ^ inoutput[minpos];
		}
	}
	return true;
}