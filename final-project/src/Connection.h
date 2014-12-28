#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>	// for memcpy(), etc;
#include <stdlib.h>	// for atoi(), etc;
#include <unistd.h>	// for gethostname(), etc;
#include <ctype.h>	// for tolower(), etc;
#include <iostream>

#define IPADDRESS "127.0.0.1"
#define PORT 60070
#define BUFS 1024
#define NAMS 64

using namespace std;

class Connection {
	int sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buf[BUFS];

public:
	Connection();
	virtual ~Connection();
	int Send(char* str, int size);
	int Receive(char* str, int size);
	void Quit();
};
