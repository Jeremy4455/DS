#pragma once
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class Graph {
private:
	vector<T> vertex;        // 存放顶点信息的数组
	vector<vector<int> > adj; // 存放边及其权重的邻接矩阵
	int numVertices;         // 顶点数目
	int maxVertices;         // 允许的顶点最大数目
	int numEdges;            // 边数
	int findIndex(const T& v);  //根据顶点名称找到索引
	bool hasPathHelper(int i, int j, vector<bool>& visited);    //辅助判断两个顶点是否有路径
	void printAllPathsHelper(int i, int j, vector<bool>& visited, vector<int>& path);   //辅助找出两个顶点间的所有路径

public:
	Graph(int maxV);										//	构造函数
	~Graph();												//	析构函数
	Graph(const Graph<T>& other);							//	拷贝构造函数
	void addVertex(T v);									//	添加顶点
	void addEdge(const T& v1, const T& v2, int weight=1);	//	添加边
	bool hasPath(const T& v1, const T& v2);					//	判断两个顶点间是否存在路径
	void printAllPaths(const T& v1, const T& v2);			//	输出顶点间所有简单路径
	void Display() const;									//	输出函数
	Graph<T>& operator=(const Graph<T>& other);				//	赋值运算符重载
	//friend ostream& operator<<(ostream& os, const Graph<T>& graph);	由于定义了Display函数，所以不需要定义为友元函数即可实现
};

template<typename T>
inline Graph<T>::Graph(int maxV) {
	numVertices = 0;
	maxVertices = maxV;
	numEdges = 0;
	adj.resize(maxV);
	for (int i = 0; i < maxV; i++) {
		adj[i].resize(maxV);
	}
}

template<typename T>
inline Graph<T>::~Graph()
{
	for (int i = 0; i < maxVertices; i++) {
		adj[i].clear();
	}
	adj.clear();
	vertex.clear();
}

template<typename T>
inline Graph<T>::Graph(const Graph<T>& other)
{
	this->maxVertices = other.maxVertices;
	this->numVertices = other.numVertices;
	this->numEdges = other.numEdges;
	for (int i = 0; i < other.numVertices; i++) {
		this->vertex[i] = other.vertex[i];
	}
	for (int i = 0; i < other.numVertices; i++) {
		for (int j = 0; j < other.numVertices; j++) {
			this->adj[i][j] = other.adj[i][j];
		}
	}
}

template<typename T>
inline void Graph<T>::addVertex(T v) {
	if (numVertices < maxVertices) {
		vertex.push_back(v);
		numVertices++;
	}
	else {
		cout << "Graph is full." << endl;
	}
}

template<typename T>
inline void Graph<T>::addEdge(const T& v1, const T& v2, int weight) {
	int i = findIndex(v1);
	int j = findIndex(v2);
	if (i >= 0 && j >= 0) {
		adj[i][j] = weight;
		adj[j][i] = weight;
		numEdges++;
	}
	else {
		cout << "Invalid vertices" << endl;
	}
}

template<typename T>
inline int Graph<T>::findIndex(const T& v) {
	for (int i = 0; i < numVertices; i++) {
		if (vertex[i] == v) {
			return i;
		}
	}
	return -1;
}

template<typename T>
inline bool Graph<T>::hasPath(const T& v1, const T& v2) {
	int i = findIndex(v1);
	int j = findIndex(v2);
	if (i < 0 || j < 0) {
		return false;
	}
	vector<bool> visited(numVertices, false);
	return hasPathHelper(i, j, visited);
}

template<typename T>
inline bool Graph<T>::hasPathHelper(int i, int j, vector<bool>& visited) {
	visited[i] = true;
	if (i == j) {
		return true;
	}
	for (int k = 0; k < numVertices; k++) {
		if (adj[i][k] > 0 && !visited[k]) {
			if (hasPathHelper(k, j, visited)) {
				return true;
			}
		}
	}
	return false;
}

template<typename T>
inline void Graph<T>::printAllPaths(const T& v1, const T& v2) {
	int i = findIndex(v1);
	int j = findIndex(v2);
	if (i < 0 || j < 0) {
		cout << "Invalid vertices" << endl;
		return;
	}
	vector<bool> visited(numVertices, false);
	vector<int> path;
	path.push_back(i);
	printAllPathsHelper(i, j, visited, path);
}

template<typename T>
inline void Graph<T>::printAllPathsHelper(int i, int j, vector<bool>& visited, vector<int>& path) {
	visited[i] = true;
	path.push_back(i);
	if (i == j) {
		for (int k = 0; k < path.size(); k++) {
			cout << vertex[path[k]] << " ";
		}
		cout << endl;
	}
	else {
		for (int k = 0; k < numVertices; k++) {
			if (adj[i][k] != 0 && !visited[k]) {
				printAllPathsHelper(k, j, visited, path);
			}
		}
	}
	visited[i] = false;
	path.pop_back();
}

template<typename T>
inline void Graph<T>::Display() const{
	cout << "Vertices: ";
	for (int i = 0; i < numVertices; i++) {
		cout << vertex[i] << " ";
	}
	cout << endl;
	cout << "Edges:" << endl;
	for (int i = 0; i < numVertices; i++) {
		for (int j = i + 1; j < numVertices; j++) {
			if (adj[i][j] != 0) {
				cout << vertex[i] << " -- " << vertex[j] << " : " << adj[i][j] << endl;
			}
		}
	}
}

template <typename T>
Graph<T>& Graph<T>::operator=(const Graph<T>& other) {
	if (this != &other) {
		this->maxVertices = other.maxVertices;
		this->numVertices = other.numVertices;
		this->numEdges = other.numEdges;
		this->vertex.clear();
		for (int i = 0; i < other.numVertices; i++) {
			this->vertex.push_back(other.vertex[i]);
		}
		this->adj.clear();
		for (int i = 0; i < other.numVertices; i++) {
			this->adj.push_back(other.adj[i]);
		}
	}
	return *this;
}

template <typename T>
ostream& operator<<(ostream& os, const Graph<T>& graph) {
	graph.Display();
	return os;
}

