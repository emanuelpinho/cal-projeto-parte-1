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
	int cobertura;
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T> ;
	friend class Vertex<T> ;

	double getWeight() const;
	int getCobertura() const;

	void setCobertura(int cobertura);
};

template<class T>
Edge<T>::Edge(Vertex<T> *d, double w) :
		dest(d), weight(w) {
}

template<class T>
double Edge<T>::getWeight() const {
	return this->weight;
}

template<class T>
void Edge<T>::setCobertura(int cobertura) {
	this->cobertura = cobertura;
}

template<class T>
int Edge<T>::getCobertura() const {
	return this->cobertura;
}

/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */


 template<class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;

	//exercicio 5
	int numCycles;
	void dfsVisit(Vertex<T> *v);
	void dfsVisit();

public:
	bool addVertex(const T &in, bool armazem, bool posto);
	bool addEdge(const T &sourc, const T &dest, double w);
	int edgeWeight(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<Vertex<T> *> getVertexSet() const;
	int getNumVertex() const;

	//exercicio 5
	Vertex<T>* getVertex(const T &v) const;
	void resetIndegrees();
	int getNumCycles();
	bool isDAG();

};

template<class T>
int Graph<T>::edgeWeight(const T &sourc, const T &dest) {
	int c = 0;

	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for (; it != ite; it++) {
		if ((*it)->info == sourc || (*it)->info == dest) {
			if ((*it)->getArmazem())
				c++;
		}
	}

	return c;
}

template<class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
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
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
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
