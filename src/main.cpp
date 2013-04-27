#include "Graph.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "graphviewer.h"

using namespace std;

Graph<int> myGraph;

void readFromFile(ifstream &isG) {
	string tipo, info, armazem, vertice1, vertice2, peso;
	bool temArmazem;
	int number, infoVertex1, infoVertex2, weight;

	while (!isG.eof()) {

		getline(isG, tipo);

		if (tipo == "vertice") {
			getline(isG, info);
			getline(isG, armazem);

			number = atoi(info.c_str());

			if (armazem == "0")
				temArmazem = false;
			else
				temArmazem = true;

			myGraph.addVertex(number, temArmazem);
		}

		else if (tipo == "aresta") {

			getline(isG, vertice1);
			getline(isG, vertice2);
			getline(isG, peso);

			infoVertex1 = atoi(vertice1.c_str());
			infoVertex2 = atoi(vertice2.c_str());
			weight = atoi(peso.c_str());

			myGraph.addEdge(infoVertex1, infoVertex2, weight);
			myGraph.addEdge(infoVertex2, infoVertex1, weight);

		} else {
			break;
			cout << "Ficheiro num formato errado";
			exit(1);
		}
	}

}

int main() {
	/*
	 cout << " Que mapa pretende fazer a cobertura? \n\n";
	 cout << " 1 - Mapa com 5 quarteirões(2 com armazem) \n";
	 cout << " 2 - Mapa com 5 quarteirões(sem armazens) \n";
	 cout << " 3 - Mapa com 20 quarteirões (sem armazens) \n";
	 cout << " 4 - Mapa com 20 quarteirões (com 5 armazens) \n";
	 cout << " 5 - Mapa com 50 quarteirões (com 12 armazens) \n";
	 cout << " 6 - SAIR \n\n\n";

	 int escolha;
	 cin >> escolha;
	 cin.clear();
	 cin.ignore(100, '\n');
	 /


	 /
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
	 }*/

	ifstream isGraph("grafo.txt");

	if (!isGraph) {
		cout << "ERROR!";
		exit(1);
	}
	readFromFile(isGraph);
	myGraph.extractToViewer();

	double minCoverage = myGraph.getMinCoverage();
	double coverage = 0;
	while (coverage == 0) {
		cout << "Capacidade dos postos de vigilia (minimo: " << minCoverage
				<< "): ";
		cin >> coverage;
		if (coverage < minCoverage) {
			cout << "Capacidade inválida" << endl;
			coverage = 0;
		}
	}
	// define o alcance dos postos de vigília
	myGraph.setCoverage(coverage);

	myGraph.placeVigilance();


	myGraph.extractFinal();




	getchar();
	return 0;
}
