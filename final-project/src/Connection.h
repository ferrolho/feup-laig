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
using namespace std;

const char IPADDRESS[256] = "127.0.0.1";
const int PORT = 60070;
const int BUF_MAX_SIZE = 1024;
// const int NAMS = 64;

enum MessageType {
	INVALID, OK, CONTINUE_JUMP, CONTINUE_CAPTURE, RECEIVE_2_CHECKERS, RECEIVE_1_CHECKER
};

class Message {
private:
	MessageType type;
	string content;

public:
	Message(MessageType type) {
		this->type = type;
	}

	~Message() {
	}

	bool isValid() {
		return type != INVALID;
	}

	MessageType getType() {
		return type;
	}

	string getContent() {
		return content;
	}

	void setContent(const string& str) {
		content = str;
	}
};

class Connection {
	int sock;
	struct sockaddr_in server;
	struct hostent* hp;
	char buffer[BUF_MAX_SIZE];

public:
	Connection();
	virtual ~Connection();

	Message* initialize();
	void terminate();

	int send(const string& message);
	Message* receive();
};
