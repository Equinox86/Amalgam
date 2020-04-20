#include "network.h"



amal_net::amal_net() {
	udp_sock = socket(AF_INET,SOCK_DGRAM,0);
	node_id = -1;
	max_req = 0; 
	cluster_size = 0;
}

void amal_net::net_msg(string msg, string remote_server) { 
	
	//Get IP and Port
	string remote_ip = remote_server.substr(0,remote_server.find(":")); 
	string remote_port = remote_server.substr(remote_server.find(":")+1,remote_server.length());

	//Update the SockAddrIn Struct
	server.sin_addr.s_addr = inet_addr(remote_ip.c_str());
	server.sin_port = htons(stoi(remote_port));
	inet_pton(AF_INET, remote_ip.c_str(), &(server.sin_addr));

	//Send Message over DUP
	sendto(udp_sock, msg.c_str(), strlen(msg.c_str()), 0, (struct sockaddr*)&server, sizeof(server));
}

void amal_net::server_init(){ 
	//Port and Address Settings
	int port = 9100;
	string address = "192.168.0.131";

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(address.c_str());
	server.sin_port = htons(port);
	int b = bind(udp_sock, (struct sockaddr*)&server, sizeof(server));
	if(b<0) { 
		perror("Error");
		return;
	} else {
		printf("%s [%s:%d]\n","Amalgam server listening on: ",address.c_str(),port);
	}
}

int amal_net::request_id(){

	//Open the ClusterSeed File 
	ifstream cluster_seed; 
	cluster_seed.open("ClusterSeed",ios::in); 
	if(!cluster_seed.is_open()){
		perror("Cannot connect to network"); 
		return -1;
	} else { 
		while(!cluster_seed.eof()) { 
			string remote_server= "";
			getline(cluster_seed,remote_server);

			//Attempt contact 
			net_msg("REQID",remote_server);
			cluster_size++;
		}
	}
	printf("No config found, reaching out to cluster size : [%d] \n", );
}