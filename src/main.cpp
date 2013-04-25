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

			getline(isG,armazemAresta);
			getline(isG, vertice1);
			getline(isG, vertice2);


			infoVertex1 = atoi(vertice1.c_str());
			infoVertex2 = atoi(vertice2.c_str());
			infoAresta = atoi(armazemAresta.c_str());


			int weight = 1;

			if (infoAresta == 1 )
				weight = 2;


			myGraph.addEdge(infoVertex1, infoVertex2, weight);
		} else {
			break;
			cout << "Ficheiro num formato errado";
			exit(1);
		}
	}

}

/*void extractToViewer() {

	GraphViewer *gv = new GraphViewer(600, 600, true, 7772);

	gv->createWindow(600, 600);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("lightGray");

	vector<Vertex<int> *> vertices = myGraph.getVertexSet();

	for (int i = 0; i < vertices.size(); i++) {
		int c = vertices[i]->getInfo();
		gv->addNode(c);
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
				gv->setEdgeColor(arestas, "blue");
			arestas++;
		}

		gv->rearrange();
	}


	//getchar();
}

void extractFinal() {

	GraphViewer *gv2 = new GraphViewer(600, 600, true, 7773);

	gv2->createWindow(600, 600);
	gv2->defineEdgeColor("blue");
	gv2->defineVertexColor("lightGray");

	vector<Vertex<int> *> vertices = myGraph.getVertexSet();

	for (int i = 0; i < vertices.size(); i++) {
		int c = vertices[i]->getInfo();
		gv2->addNode(c);
		if(vertices[i]->getpostoVigilia()){
			gv2->setVertexColor(i + 1, "black");
		}
	}

	int arestas = 1;
	int origem, destino;
	for (int i = 0; i < vertices.size(); i++) {
		origem = vertices[i]->getInfo();
		vector<Edge<int> > adj2 = vertices[i]->getEdges();
		for (int c = 0; c < adj2.size(); c++) {
			destino = adj2[c].getDest()->getInfo();
			gv2->addEdge(arestas, origem, destino, EdgeType::UNDIRECTED);
			int weight = myGraph.edgeWeight(origem, destino);
			if(weight == 1)
				gv2->setEdgeColor(arestas, "green");
			else
				gv2->setEdgeColor(arestas, "blue");
			arestas++;
		}

		gv2->rearrange();
	}



}*/

int main() {

	ifstream isGraph("grafo.txt");

	if (!isGraph) {
		cout << "ERROR!";
		exit(1);
	}

	readFromFile(isGraph);
	myGraph.extractToViewer();

	myGraph.cobrirArmazens();

	myGraph.extractFinal();


	getchar();


	return 0;

}
