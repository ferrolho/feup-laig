#include <iostream>
#include <exception>
#include <ctime>

#include "CGFapplication.h"
#include "GraphScene.h"
#include "GraphSceneUI.h"
#include "Connection.h"

using std::cout;
using std::exception;

/*int main(int argc, char* argv[]) {
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
}*/

int main() {
	Connection* conn = new Connection();
	conn->Quit();
	return 0;
}

