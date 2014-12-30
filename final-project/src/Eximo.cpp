#include "Eximo.h"

#include <cmath>
#include <cstring>
#include <stdio.h>

vector<string> explode(string const& s, char delim) {
	vector<string> result;
	istringstream iss(s);

	for (string token; getline(iss, token, delim);)
		result.push_back(token);

	return result;
}

Eximo::Eximo(const string& eximo) {
	/* [
	 * [[emptyCell,whiteCell,whiteCell,whiteCell,whiteCell,whiteCell,whiteCell,emptyCell],
	 *  [emptyCell,whiteCell,whiteCell,whiteCell,whiteCell,whiteCell,whiteCell,emptyCell],
	 *  [emptyCell,whiteCell,whiteCell,emptyCell,emptyCell,whiteCell,whiteCell,emptyCell],
	 *  [emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell],
	 *  [emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell,emptyCell],
	 *  [emptyCell,blackCell,blackCell,emptyCell,emptyCell,blackCell,blackCell,emptyCell],
	 *  [emptyCell,blackCell,blackCell,blackCell,blackCell,blackCell,blackCell,emptyCell],
	 *  [emptyCell,blackCell,blackCell,blackCell,blackCell,blackCell,blackCell,emptyCell]],
	 * [16,16],
	 * whitePlayer,
	 * pvp
	 * ] */

	unsigned first = eximo.find("[[[");
	unsigned last = eximo.find("]]");
	string eximoStr = eximo.substr(first, last - first);
	cout << "eximoStr:" << endl << eximoStr << endl << endl;

	char *eximoCStr = new char[eximoStr.length() + 1];
	strcpy(eximoCStr, eximoStr.c_str());

	vector<string> temp;
	int line = 0;
	char *p = strtok(eximoCStr, "[,]");
	while (p) {
		printf("dasd\n");
		printf("line %d: %s\n", line++, p);
		temp.push_back(p);
		p = strtok(NULL, "[,]");
	}

	vector<vector<string> > strBoard;
	vector<string> temp2;
	for (unsigned int i = 0; i < temp.size(); i++) {
		temp2.push_back(temp[i]);

		int size = sqrt(temp.size());
		if ((i + 1) % size == 0) {
			cout << i << endl;
			strBoard.push_back(temp2);
			temp2.clear();
		}
	}

	cout << endl << "teste" << endl;
	for (unsigned int i = 0; i < strBoard.size(); i++) {
		cout << "@@_";
		for (unsigned int j = 0; j < strBoard[i].size(); j++)
			cout << strBoard[i][j] << "_";
		cout << endl;
	}

	delete[] eximoCStr;
}

Eximo::~Eximo() {
}
