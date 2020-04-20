#include <iostream>
#include <fstream>
#include <string.h>
#include <arpa/inet.h>
#include <map>


//This class should do the following: 
	// 1. Handle incoming messages from remote Nodes
		//Incomming Messages Must be relayed to the calling Method
	// 2. Send Messages to Remote Nodes

using namespace std;
class amal_net
{
public:

	int udp_sock;
	int node_id;
	int max_req;
	int cluster_size;

	struct  sockaddr_in server;
	socklen_t sock_size= sizeof(server);
	
	amal_net();
	void server_init();
	void net_msg(string msg, string remote_server);
	int request_id();

};