#include "Connection.h"

#include "Utilities.h"

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

int Connection::send(const string& message) {
	// write message to socket
	if (write(sock, message.c_str(), message.length()) < 0) {
		printf("Connection: send() error");
		return 1;
	}

	cout << "Sent: " << message << endl;

	return 0;
}

Message* Connection::receive() {
	// clear buffer
	memset(buffer, 0, BUF_MAX_SIZE);

	// read message from socket to buffer
	if (read(sock, buffer, BUF_MAX_SIZE) < 0) {
		printf("Connection: receive() error");
		return new Message(false);
	}

	string msg = buffer;
	cout << "Received: " << msg << endl;

	if (msg.find("ok") != 0)
		return new Message(false);

	Message* message = new Message(true);

	message->setContent(getSubstringBetween(msg, "(", ")"));

	return message;
}

void Connection::quit() {
	cout << "Terminating connection." << endl;

	send("quit.\n");

	string message;
	receive();

	cout << "Connection terminated." << endl;
}
