#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <string>
#include <list>
#include <limits>
#include <cmath>
#include <iostream>
#include <climits>
#include "graphviewer.h"
using namespace std;

template<class T> class Edge;
template<class T> class Graph;

/* ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

template<class T>
class Vertex {
	T info;
	vector<Edge<T> > adj;
	bool armazem;
	bool postoVigilia;
	int indegree;
	bool visited;
public:

	Vertex(T in, bool armazem, bool posto);
	friend class Graph<T> ;

	void addEdge(Vertex<T> *dest, double w);

	T getInfo() const;

	bool getArmazem() const;
	bool getpostoVigilia() const;
	bool getVisited() const;
	int getIndegree() const;
	vector<Edge<T> > getEdges() const;

	void setPostoVigilia(bool vigilia);
	void setVisited(bool visited);

};

template<class T>
Vertex<T>::Vertex(T in, bool armazem, bool posto) :
		info(in), armazem(armazem), postoVigilia(posto), indegree(0) {
}

template<class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template<class T>
vector<Edge<T> > Vertex<T>::getEdges() const {
	return adj;
}

template<class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest, w);
	adj.push_back(edgeD);
}

template<class T>
bool Vertex<T>::getArmazem() const {
	return this->armazem;
}

template<class T>
bool Vertex<T>::getVisited() const {
	return this->visited;
}

template<class T>
int Vertex<T>::getIndegree() const {
	return this->indegree;
}

template<class T>
bool Vertex<T>::getpostoVigilia() const {
	return this->postoVigilia;
}

template<class T>
void Vertex<T>::setPostoVigilia(bool vigilia) {
	this->postoVigilia = vigilia;
}

template<class T>
void Vertex<T>::setVisited(bool visited) {
	this->visited = visited;
}

/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */

template<class T>
class Edge {
	Vertex<T> * dest;
	int weight;
public:
	Edge(Vertex<T> *d, int w);
	friend class Graph<T> ;
	friend class Vertex<T> ;

	double getWeight() const;
	void setWeight(int peso);

	void decWeight();
	Vertex<T> * getDest() const;

};

template<class T>
Edge<T>::Edge(Vertex<T> *d, int w) :
		dest(d), weight(w) {
}

template<class T>
double Edge<T>::getWeight() const {
	return this->weight;
}

template<class T>
void Edge<T>::setWeight(int peso) {
	this->weight = peso;
}

template<class T>
void Edge<T>::decWeight(){
	cout << "\n\n\nAntes : " << weight;
	int temp = this->weight;
	temp--;
	this->weight = temp;
	cout << "\n\n\nDepois : " << weight;
}

template<class T>
Vertex<T> * Edge<T>::getDest() const {
	return this->dest;
}



/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */

template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	vector<int> verticesMaiores; // diz quais os vertices que tem mais ruas por cobrir
	void dfs(Vertex<T> *v, vector<T> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();

public:
	bool addVertex(const T &in, bool armazem, bool posto);
	bool addEdge(const T &sourc, const T &dest, int w);
	int edgeWeight(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;
	void cobrirArmazens();
	void verticesPrioritarios();
	void adicionarPosto();
	int verticeComMaisPrioridade(int verticeInfo);
	void preencherVertice(int verticeInfo);
	void extractToViewer();
	void extractFinal();

	//exercicio 5
	Vertex<T>* getVertex(const T &v) const;
	void resetIndegrees();
	int getNumCycles();
	bool isDAG();

};

template<class T>
int Graph<T>::edgeWeight(const T &sourc, const T &dest) {

	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
		typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
		for (; it != ite; it++) {
			if ((*it)->info == sourc) {
				for(int i = 0; i < (*it)->getEdges().size(); i++)
				if (dest == (*it)->getEdges()[i].getDest()->getInfo()){
					cout << "\n\nO caralho do tamanho e: " << (*it)->getEdges()[i].getWeight() << "\n\n";
					return ((*it)->getEdges()[i].getWeight());
				}
			}
		}

}

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template<class T>
void Graph<T>::extractToViewer(){


	GraphViewer *gv = new GraphViewer(600, 600, true, 7772);

		gv->createWindow(600, 600);
		gv->defineEdgeColor("blue");
		gv->defineVertexColor("lightGray");


		for (int i = 0; i < vertexSet.size(); i++) {
			int c = vertexSet[i]->getInfo();
			gv->addNode(c);
		}

		int arestas = 1;
		int origem, destino;
		for (int i = 0; i < vertexSet.size(); i++) {
			origem = vertexSet[i]->getInfo();
			for (int c = 0; c < vertexSet[i]->getEdges().size(); c++) {
				destino = vertexSet[i]->getEdges()[c].getDest()->getInfo();
				gv->addEdge(arestas, origem, destino, EdgeType::UNDIRECTED);
				int weight = edgeWeight(origem, destino);
				if(weight == 2)
					gv->setEdgeColor(arestas, "red");
				else
					gv->setEdgeColor(arestas, "blue");
				arestas++;
			}

			gv->rearrange();
		}
}

template<class T>
void Graph<T>::extractFinal(){


	GraphViewer *gv2 = new GraphViewer(600, 600, true, 7773);

		gv2->createWindow(600, 600);
		gv2->defineEdgeColor("blue");
		gv2->defineVertexColor("lightGray");


		for (int i = 0; i < vertexSet.size(); i++) {
			int c = vertexSet[i]->getInfo();
			gv2->addNode(c);
			if(vertexSet[i]->getpostoVigilia()){
				gv2->setVertexColor(i + 1, "black");
			}
		}

		int arestas = 1;
		int origem, destino;
		for (int i = 0; i < vertexSet.size(); i++) {
			origem = vertexSet[i]->getInfo();
			for (int c = 0; c < vertexSet[i]->getEdges().size(); c++) {
				destino = vertexSet[i]->getEdges()[c].getDest()->getInfo();
				gv2->addEdge(arestas, origem, destino, EdgeType::UNDIRECTED);
				int weight = edgeWeight(origem, destino);
				if(weight <= 0)
					gv2->setEdgeColor(arestas, "green");
				else
					gv2->setEdgeColor(arestas, "blue");
				arestas++;
			}

			gv2->rearrange();
		}
}


template<class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
int Graph<T>::getNumCycles() {
	numCycles = 0;
	dfsVisit();
	return this->numCycles;
}

template<class T>
bool Graph<T>::isDAG() {
	return (getNumCycles() == 0);
}

template<class T>
bool Graph<T>::addVertex(const T &in, bool armazem, bool posto) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++)
		if ((*it)->info == in)
			return false;
	Vertex<T> *v1 = new Vertex<T>(in, armazem, posto);
	vertexSet.push_back(v1);
	return true;
}

template<class T>
void Graph<T>::cobrirArmazens() {

	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->getArmazem()) {
			(*it)->setPostoVigilia(true);
			for (int i = 0; i < (*it)->getEdges().size(); i++){
				int peso = (*it)->getEdges()[i].getWeight();
				peso--;
				cout << "\n\nllololo: " << peso;
				(*it)->getEdges()[i].setWeight(peso);
				//(*it)->getEdges()[i].decWeight();
				cout << "\n\nlalala: " << (*it)->getEdges()[i].getWeight();
			}
		}
	}
}

template<class T>
int Graph<T>::verticeComMaisPrioridade(int verticeInfo) {


	return verticeInfo;
}

template<class T>
void Graph<T>::preencherVertice(int verticeInfo) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
		for (; it != ite; it++) {
			if((*it)->getInfo() == verticeInfo){
				(*it)->setPostoVigilia(true);
				for (int i = 0; i < (*it)->getEdges().size(); i++)
					(*it)->getEdges()[i].decCobertura();
				it = vertexSet.end();
				break;									//saber se e preciso um ou outro, para sair quando encontrar vertice
			}
		}

}

template<class T>
void Graph<T>::adicionarPosto() { //Esta funcao ve quais os vertices com mais arestas por preencher, qual e mais prioritario e coloca posto

	verticesPrioritarios();

	while (verticesMaiores.size() > 0) {
		if (verticesMaiores.size() == 1)
			preencherVertice(verticesMaiores[0]);
		else
			for (int i = 0; i < verticesMaiores.size(); i++) {
				int verticePrioritario = verticeComMaisPrioridade(verticesMaiores[i]);
				preencherVertice(verticePrioritario);
			}

	}
}

template<class T>
void Graph<T>::verticesPrioritarios() { //FAZ RETURN DE UM VETOR DE VERTICES COM O MAIOR NUMERO DE ARESTAS DESCOBERTAS

	int nRuasPorCobrir;
	int maiorNumero = 0;
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		nRuasPorCobrir = 0;
		for (int i = 0; i < (*it)->getEdges().size(); i++)
			if ((*it)->getEdges()[i].getCobertura() > 0)
				nRuasPorCobrir++;

		if (nRuasPorCobrir > maiorNumero) {
			verticesMaiores.clear();
			verticesMaiores.push_back((*it)->getInfo());
			maiorNumero = nRuasPorCobrir;
		} else if (nRuasPorCobrir == maiorNumero && nRuasPorCobrir != 0)
			verticesMaiores.push_back((*it)->getInfo());
	}

}

template<class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, int w) {
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	int found = 0;
	Vertex<T> *vS, *vD;
	while (found != 2 && it != ite) {
		if ((*it)->info == sourc) {
			vS = *it;
			found++;
		}
		if ((*it)->info == dest) {
			vD = *it;
			found++;
		}
		it++;
	}
	if (found != 2)
		return false;
	vD->indegree++;
	vS->addEdge(vD, w);

	return true;
}

template<class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	vector<T> res;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfs(*it, res);
	return res;
}

template<class T>
void Graph<T>::dfs(Vertex<T> *v, vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++)
		if (it->dest->visited == false) {
			//cout << "ok ";
			dfs(it->dest, res);
		}
}

template<class T>
Vertex<T>* Graph<T>::getVertex(const T &v) const {
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v)
			return vertexSet[i];
	return NULL;
}

template<class T>
void Graph<T>::resetIndegrees() {
	//colocar todos os indegree em 0;
	for (unsigned int i = 0; i < vertexSet.size(); i++)
		vertexSet[i]->indegree = 0;

	//actualizar os indegree
	for (unsigned int i = 0; i < vertexSet.size(); i++) {
		//percorrer o vector de Edges, e actualizar indegree
		for (unsigned int j = 0; j < vertexSet[i]->adj.size(); j++) {
			vertexSet[i]->adj[j].dest->indegree++;
		}
	}
}

template<class T>
void Graph<T>::dfsVisit() {
	typename vector<Vertex<T>*>::const_iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite = vertexSet.end();
	for (; it != ite; it++)
		(*it)->visited = false;
	it = vertexSet.begin();
	for (; it != ite; it++)
		if ((*it)->visited == false)
			dfsVisit(*it);
}

template<class T>
void Graph<T>::dfsVisit(Vertex<T> *v) {
	v->processing = true;
	v->visited = true;
	typename vector<Edge<T> >::iterator it = (v->adj).begin();
	typename vector<Edge<T> >::iterator ite = (v->adj).end();
	for (; it != ite; it++) {
		if (it->dest->processing == true)
			numCycles++;
		if (it->dest->visited == false) {
			dfsVisit(it->dest);
		}
	}
	v->processing = false;
}

#endif /* GRAPH_H_ */
