#include "Graph.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "graphviewer.h"

using namespace std;

Graph<int> myGraph;

void readFromFile(ifstream &isG) {
	string tipo, info, armazem, posto, vertice1, vertice2;
	bool temArmazem, temPosto;
	int number, infoVertex1, infoVertex2;

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

			getline(isG, vertice1);
			getline(isG, vertice2);

			infoVertex1 = atoi(vertice1.c_str());
			infoVertex2 = atoi(vertice2.c_str());

			int weight = myGraph.edgeWeight(infoVertex1, infoVertex2);

			if (weight != 2)
				weight = 1;

			myGraph.addEdge(infoVertex1, infoVertex2, weight);
		} else {
			cout << "Ficheiro num formato errado";
			exit(1);
		}
	}

}

void extractToViewer() {

	GraphViewer *gv = new GraphViewer(600, 600, true, 7772);

	gv->createWindow(600, 600);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("lightGray");

	vector<Vertex<int> *> vertices = myGraph.getVertexSet();

	for (int i = 0; i < vertices.size(); i++) {
		int c = vertices[i]->getInfo();
		gv->addNode(c);
		if (vertices[i]->getArmazem()) {
			gv->setVertexColor(i + 1, "blue");
		}
	}

	int arestas = 1;
	int origem, destino;
	for (int i = 0; i < vertices.size(); i++) {
		origem = vertices[i]->getInfo();
		vector<Edge<int> > adj2 = vertices[i]->getEdges();
		for (int c = 0; c < adj2.size(); c++) {
			destino = adj2[c].getDest()->getInfo();
			gv->addEdge(arestas, origem, destino, EdgeType::UNDIRECTED);
			int weight = myGraph.edgeWeight(origem, destino);
			if(weight == 2)
				gv->setEdgeColor(arestas, "red");
			else
				gv->setEdgeColor(arestas, "yellow");
			arestas++;
		}

		gv->rearrange();
	}


	getchar();
}

int main() {

	ifstream isGraph("grafo.txt");

	if (!isGraph) {
		cout << "ERROR!";
		exit(1);
	}

	readFromFile(isGraph);
	extractToViewer();

	//myGraph.cobrirArmazens();



	return 0;

}
