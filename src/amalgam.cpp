#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <sys/time.h>
#include <time.h>
#include <mutex>
#include <thread>

#include "security.h"
#include "network.h"

using namespace std; 

/* Premise:  
* 1. Files exist nowhere. They Exist in encrypted elements that are load spread across a network
* 2. Files are Downloaded on the fly  reconstructed from private keys. 
* 3. Persistent storage is always reconstructed based on local files  bytes available in the swarm.
*/

//Global Communication Object

string getTimeStamp() { 
	
  char buff[30];
  struct timeval tv;
  time_t curtime;
  gettimeofday(&tv, NULL); 
  curtime=tv.tv_sec;

  strftime(buff,sizeof(buff),"%T",localtime(&curtime));
  //string out_string = string(buff)+ to_string(tv.tv_sec);

  return string(buff);
}

map <string, int>  populate_commands() { 
	map<string, int> cmd_list; 

	cmd_list["REQID"] = 0; 
	cmd_list["RESID"] = 1; 
	
	return cmd_list;
}

int main (int argc, char ** argv){
	
	//Generate map for command arguments 
	map <string, int> cmd_list = populate_commands();

	amal_net a_conn; 
	
	//Init Server
	a_conn.server_init(); 

	//Request an ID number
	a_conn.request_id();

	//Character Buffer to read in from  UDP data in
	char buff[1024];

	while(true){ 
		int rlen = recvfrom(a_conn.udp_sock, buff ,sizeof(buff),0,(struct sockaddr *)&a_conn.server,&a_conn.sock_size) ; 
		
		buff[rlen] = 0;

		string origin = string(inet_ntoa(a_conn.server.sin_addr)) + ":" + to_string(ntohs(a_conn.server.sin_port));
		printf("%s [%s] (%d bytes) received from Origin %s\n",getTimeStamp().c_str(), buff, rlen, origin.c_str());

		//Translate to COMMAND
		string cmd = { buff[0],buff[1],buff[2] ,buff[3],buff[4]};
		int cmd_int=-1; 
		auto cmd_iter = cmd_list.find(cmd);
		if(cmd_iter == cmd_list.end()){ 
			printf("Invald Command: [%s]\n",cmd.c_str());
			continue;
		} else { 
			cmd_int = cmd_iter -> second;
		}

		//Strings are easier to work with.. 
		string buff_string = string(buff);

		//Action the command	
		switch(cmd_int){ 
			case(0)://Request for an id
				printf("%s\n","Request for Id Received" );
				if(a_conn.node_id > -1){ 
					string response = "RESID:"+ to_string(a_conn.max_req); 
					a_conn.net_msg(response,origin);
				}
			break;
			case(1)://Response from a Request for an ID
				//Extract the number
				int resp_id = atoi(buff_string.substr(buff_string.find(":")+1,buff_string.length()).c_str());
				//Compare to other responses
				if(resp_id >  );
				//Increase the response count
				//Check if all requests have been fulfilled
			break;
		}
	}




}