#include "fileman.h"
#include <vector>


file_man::file_man(){ 
	//Constructor
}



int file_man::transmit_file(string path){ 
	char * chunk = new char[CHUNKSIZE];
	ifstream base;
	base.open(path,ios::in | ios::binary);	
	if(base.is_open()){
		ofstream chunk_file;
		chunk_file.open(path.substr(0,path.find("/")) + "/chunks", fstream::out |ios::app | ios::binary);

		if(!chunk_file.is_open()){ 
			perror("Chunk Error: ");
			return -1;
		}

		//Beginning of File and read chunks until end
		base.seekg(0,ios::beg);
		while(!base.eof()) { 

			//Clear this Chunk -- Padding is set to FF
			memset(chunk,0, CHUNKSIZE);

			base.read(chunk,CHUNKSIZE);	

			uint32_t hash = MurmurHash2(chunk,CHUNKSIZE,1);
			printf("Word: [%s] Murmur2 Hash:[%u] \n",chunk, hash);
			printf("%x\n",hash );
			printf("%x%x%x%x\n",chunk[0],chunk[1],chunk[2],chunk[3]);
			
			//write an entry to the file
			chunk_file.write((char *)&hash, sizeof(hash));
			chunk_file.write(chunk, sizeof(chunk));


		}
		chunk_file.close();
		delete[] chunk;


	} else {
		perror("Error:");
		return -1;
	}
}