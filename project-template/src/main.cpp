#include <iostream>
#include <exception>
#include <ctime>

#include "CGFapplication.h"
#include "GraphScene.h"

using std::cout;
using std::exception;

int main(int argc, char* argv[]) {
	// initialize random seed
	srand(time(NULL));

	CGFapplication app = CGFapplication();

	try {
		app.init(&argc, argv);
		app.setScene(new GraphScene());
		app.setInterface(new CGFinterface());
		app.run();
	} catch (GLexception& ex) {
		cout << "Erro: " << ex.what();
		return -1;
	} catch (exception& ex) {
		cout << "Erro inesperado: " << ex.what();
		return -1;
	}

	return 0;
}
