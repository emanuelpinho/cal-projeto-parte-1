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
		exit(1);
	}

	readFromFile(isGraph);

	/*  GraphViewer *gv = new GraphViewer(600, 600, true, 7772);

	  gv->createWindow(600, 600);
	  gv->defineEdgeColor("blue");
	  gv->defineVertexColor("lightGray");

	  gv->addNode(0);
	  gv->addNode(1);
	  gv->addNode(2);
	  gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	  gv->addEdge(3, 0, 1, EdgeType::UNDIRECTED);
	  gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);
	  gv->addEdge(2, 1, 2, EdgeType::DIRECTED);

	  gv->setEdgeLabel(0, "Edge number 0");
	  gv->setEdgeColor(1, "yellow");
	  gv->setEdgeThickness(1, 5);

	  gv->setVertexColor(0, "green");

	  gv->rearrange();

	  GraphViewer *gv2 = new GraphViewer(600, 600, true, 7773);

	  gv2->createWindow(600, 600);
	  gv2->defineEdgeColor("green");
	  gv2->defineVertexColor("yellow");

	  gv2->addNode(0);
	  gv2->addNode(1);
	  gv2->addNode(2);
	  gv2->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	  gv2->addEdge(3, 0, 1, EdgeType::UNDIRECTED);
	  gv2->addEdge(1, 0, 2, EdgeType::UNDIRECTED);
	  gv2->addEdge(2, 1, 2, EdgeType::DIRECTED);

	  gv2->setEdgeLabel(0, "Edge number 0");
	  gv2->setEdgeColor(1, "yellow");
	  gv2->setEdgeThickness(1, 5);

	  gv2->setVertexColor(0, "green");

	  gv2->rearrange();



	  getchar();
*/
	return 0;

}
