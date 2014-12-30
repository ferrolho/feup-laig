#pragma once

#include <ctype.h>
#include <iostream>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

const char IPADDRESS[256] = "127.0.0.1";
const int PORT = 60070;
const int BUF_MAX_SIZE = 1024;
// const int NAMS = 64;

using namespace std;

class Connection {
	int sock;
	struct sockaddr_in server;
	struct hostent* hp;
	char buffer[BUF_MAX_SIZE];

public:
	Connection();
	virtual ~Connection();

	int send(const string& message);

	int receive(string& message);

	void quit();
};
