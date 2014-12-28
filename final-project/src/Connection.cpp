#include "Connection.h"

Connection::Connection() {
	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("Opening stream socket");
		exit(1);
	}

	/* Connect socket using server name indicated in the command line */
	server.sin_family = AF_INET;
	hp = gethostbyname(IPADDRESS);
	if (hp == NULL) {
		perror("Trying to get host by name");
		exit(2);
	}
	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port = htons(PORT);

	if (connect(sock, (struct sockaddr *) &server, sizeof server) < 0) {
		perror("Connecting stream socket");
		exit(1);
	}

	// Successful status.
	printf("Connected\n");
	getchar();
}

Connection::~Connection() {

}

int Connection::Send(char* str, int size) {
	if(write(sock, str, size) < 0) {
		printf("Connection: send() error");
		return 1;
	}

	return 0;
}

int Connection::Receive(char *str, int size) {
	if(read(sock, str, size) < 0) {
		printf("Connection: receive() error");
		return 1;
	}

	str[size] = '\0';

	printf("Prolog Answered: %s\n", str);

	return 0;
}

void Connection::Quit() {
	cout << "Asking prolog to quit" << endl;
	char buff[] = "quit.\n";
	Send(buff, 6);
	char ans[128];
	Receive(ans, sizeof(ans));
}

