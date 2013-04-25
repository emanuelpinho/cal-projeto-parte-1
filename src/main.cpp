#include "Graph.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "graphviewer.h"

using namespace std;

Graph<int> myGraph;

void readFromFile(ifstream &isG) {
	string tipo, info, armazem, posto, vertice1, vertice2, armazemAresta;
	bool temArmazem, temPosto;
	int number, infoVertex1, infoVertex2, infoAresta, pesoAresta;

	while (!isG.eof()) {

		getline(isG, tipo);

		if (tipo == "vertice") {
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

			getline(isG, armazemAresta);
			getline(isG, vertice1);
			getline(isG, vertice2);

			infoVertex1 = atoi(vertice1.c_str());
			infoVertex2 = atoi(vertice2.c_str());
			infoAresta = atoi(armazemAresta.c_str());

			int weight = 1;

			if (infoAresta == 1)
				weight = 2;

			myGraph.addEdge(infoVertex1, infoVertex2, weight);

		} else {
			break;
			cout << "Ficheiro num formato errado";
			exit(1);
		}
	}

}

int main() {

	cout
			<< "                       Que mapa pretende fazer a cobertura?                     \n\n";
	cout
			<< "                       1 - Mapa com 5 quarteirões(2 com armazem)                 \n";
	cout
			<< "                       2 - Mapa com 5 quarteirões(sem armazens)                  \n";
	cout
			<< "                       3 - Mapa com 20 quarteirões (sem armazens)                 \n";
	cout
			<< "                       4 - Mapa com 20 quarteirões (com 5 armazens)               \n";
	cout
			<< "                       5 - Mapa com 50 quarteirões (com 12 armazens)              \n";
	cout
			<< "                       6 - SAIR                                                   \n\n\n";

	int escolha;
	cin >> escolha;
	cin.clear();
	cin.ignore(100, '\n');

	ifstream isGraph("grafo.txt");

		if (!isGraph) {
			cout << "ERROR!";
			exit(1);
		}
	switch (escolha) {
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		exit(1);
	default:
		cerr << "Opcao invalida\n";
		break;
	}



	readFromFile(isGraph);
	myGraph.extractToViewer();

	myGraph.cobrirArmazens();

	while(myGraph.arestasDescobertas()){
		myGraph.adicionarPosto();

	}

	myGraph.extractFinal();



	getchar();

	return 0;

}
