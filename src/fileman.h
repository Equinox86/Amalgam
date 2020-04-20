#include <iostream>
#include <fstream>
#include <string.h>
#include "MurmurHash2.h"

#define CHUNKSIZE 4 //32 bit chunk size

using namespace std;
class file_man
{
public:
	file_man();
	int transmit_file(string path); //Open file, return filedescriptor
	int bit_sum(char * chunk);
	void mem_local_chunks(string path);

	typedef struct chunk_ref{
		bool local;
		string address;
	} chunk_ref;
	
};