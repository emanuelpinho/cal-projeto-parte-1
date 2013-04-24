#include "Graph.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

Graph<int> myGraph;

void readFromFile(ifstream &isG) {
	string tipo, info, armazem, posto, vertice1, vertice2;
	bool temArmazem, temPosto;
	int number, infoVertex1, infoVertex2;

	while (!isG.eof()) {
		getline(isG, tipo);
		if (info == "vertice") {
			getline(isG, info);
			getline(isG, armazem);
			getline(isG, posto);

			number = atoi(info.c_str());

			if (armazem == "0")
				temArmazem = false;
			else
				temArmazem = true;

			if (posto == "0")
				temPosto = false;
			else
				temPosto = true;

			myGraph.addVertex(number, temArmazem, temPosto);
		}

		else if (tipo == "aresta") {

			getline(isG, vertice1);
			getline(isG, vertice2);

			infoVertex1 = atoi(vertice1.c_str());
			infoVertex2 = atoi(vertice2.c_str());

			int weight = myGraph.edgeWeight(infoVertex1,infoVertex2);

			if(weight != 2)
				weight = 1;

			myGraph.addEdge(infoVertex1,infoVertex2, weight);
		}

		else {
			cout << "Ficheiro num formato errado";
			exit(1);
		}
	}

}

int main() {

	ifstream isGraph("grafo.txt");

	if (!isGraph) {
		cout << "ERROR!";
	}

	readFromFile(isGraph);


	return 0;

}

