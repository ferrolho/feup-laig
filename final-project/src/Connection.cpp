#include "Connection.h"

Connection::Connection() {
	// create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("Opening stream socket");
		exit(1);
	}

	// connect socket using server name indicated in the command line
	server.sin_family = AF_INET;
	hp = gethostbyname(IPADDRESS);
	if (!hp) {
		perror("Trying to get host by name");
		exit(2);
	}

	memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
	server.sin_port = htons(PORT);

	if (connect(sock, (struct sockaddr *) &server, sizeof server) < 0) {
		perror("Connecting stream socket");
		exit(1);
	}

	// successful status
	printf("Connection established.\n");
}

Connection::~Connection() {
}

int Connection::send(char* message, int size) {
	printf("Sent: %s\n", message);

	if (write(sock, message, size) < 0) {
		printf("Connection: send() error");
		return 1;
	}

	return 0;
}

int Connection::receive(char* message, int size) {
	memset(message, 0, size);

	if (read(sock, message, size) < 0) {
		printf("Connection: receive() error");
		return 1;
	}

	printf("Received: %s\n", message);

	return 0;
}

void Connection::quit() {
	cout << "Terminating connection." << endl;

	char buffer[BUFS] = "quit.\n";

	send(buffer, strlen(buffer));

	receive(buffer, BUFS);

	cout << "Connection terminated." << endl;
}
