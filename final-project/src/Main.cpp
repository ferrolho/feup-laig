#include <iostream>
#include <exception>
#include <ctime>

#include "CGFapplication.h"
#include "GraphScene.h"
#include "GraphSceneUI.h"

using std::cout;
using std::exception;

int main(int argc, char* argv[]) {
	/*
	 string command = "move(1, 2, 3, 2,";
	 command.append(eximo->toPrologString());
	 command.append(").\n");

	 connection->send(command);
	 message = connection->receive();
	 eximo->update(message);
	 cout << eximo->toString() << endl;

	 ///////
	 command = "move(6, 1, 4, 1,";
	 command.append(eximo->toPrologString());
	 command.append(").\n");

	 connection->send(command);
	 message = connection->receive();
	 eximo->update(message);
	 cout << eximo->toString() << endl;

	 ///////
	 //command = "move(3, 2, 5, 0,";
	 command = "move(3, 3, 5, 0,";
	 command.append(eximo->toPrologString());
	 command.append(").\n");

	 connection->send(command);
	 message = connection->receive();
	 eximo->update(message);
	 cout << eximo->toString() << endl;

	 connection->quit();
	 */

	// initialize random seed
	srand(time(NULL));

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);
		app.setScene(new GraphScene(argv[1]));
		app.setInterface(new GraphSceneUI());
		app.run();
	} catch (GLexception &ex) {
		cout << "Erro: " << ex.what() << endl;
		return -1;
	} catch (exception &ex) {
		cout << "Erro inesperado: " << ex.what() << endl;
		return -1;
	}

	return 0;
}

