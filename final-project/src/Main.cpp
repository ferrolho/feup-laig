#include <iostream>
#include <exception>
#include <ctime>

#include "CGFapplication.h"
#include "GraphScene.h"
#include "GraphSceneUI.h"
#include "Connection.h"

#include "Eximo.h"

using std::cout;
using std::exception;

bool prolog = 1;

int main(int argc, char* argv[]) {
	/*if (prolog) {
		Connection* connection = new Connection();

		string message;

		connection->send("initialize.\n");
		connection->receive(message);

		unsigned first = message.find("(");
		unsigned last = message.find(')');
		string eximoStr = message.substr(first, last - first);
		Eximo* eximo = new Eximo(eximoStr);
		cout << eximo->toString() << endl;
		//cout << eximo->toPrologString() << endl;

		connection->send(
				"move(0, 0, 3, 3, [[[emptyCell,whiteCell,whiteCell,whiteCell,whiteCell,whiteCell,whiteCell,emptyCell],[emptyCell,whiteCell,whiteCell,whiteCell,whiteCell,whiteCell,whiteCell,emptyCell],[emptyCell,whiteCell,whiteCell,emptyCell,emptyCell,whiteCell,whiteCell,emptyCell],[emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell],[emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell],[emptyCell,blackCell,blackCell,emptyCell,emptyCell,blackCell,blackCell,emptyCell],[emptyCell,blackCell,blackCell,blackCell,blackCell,blackCell,blackCell,emptyCell],[emptyCell,blackCell,blackCell,blackCell,blackCell,blackCell,blackCell,emptyCell]],[16,16],whitePlayer,pvp]).\n");
		connection->receive(message);

		connection->quit();
	} else {*/
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
	//}

	return 0;
}

