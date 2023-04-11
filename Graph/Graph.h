#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

template <typename T, typename W>
class Graph {
private:
	vector<T> vertex;        // 存放顶点信息的数组
	vector<vector<W>> adj;	 // 存放边及其权重的邻接矩阵
	int numVertices;         // 顶点数目
	int maxVertices;         // 允许的顶点最大数目
	int numEdges;            // 边数
	int findIndex(const T& v);  //根据顶点名称找到索引
	bool hasPathHelper(int i, int j, vector<bool>& visited);    //辅助判断两个顶点是否有路径
	void printAllPathsHelper(int i, int j, vector<bool>& visited, vector<int>& path);   //辅助找出两个顶点间的所有路径
	int findParent(vector<int>& parent, int u);
	void findShortestPathHelper(int i, int j, vector<bool>& visited, vector<int>& path, vector<int>& shortest_path, W& weight);
public:
	Graph(int maxV);										//	构造函数
	Graph(int maxV, vector<T>vertex);						//	构造函数
	~Graph();												//	析构函数
	Graph(const Graph<T, W>& other);						//	拷贝构造函数
	void addVertex(T v);									//	添加顶点
	void addEdge(const T& v1, const T& v2, int weight=1);	//	添加边
	void addEdge(int i, int j, int weight);
	void removeEdge(int i, int j);
	bool hasPath(const T& v1, const T& v2);					//	判断两个顶点间是否存在路径
	void printAllPaths(const T& v1, const T& v2);			//	输出顶点间所有简单路径
	void Display() const;									//	输出函数
	Graph<T, W>& operator=(const Graph<T, W>& other);		//	赋值运算符重载
	Graph<T, W> Kruskal();									//	Kruskal算法
	Graph<T, W> Prim();										//	Prim算法
	Graph<T, W> breakCircle();								//	破圈法
	bool findCircle(int v, vector<bool>& visited, vector<int>& circle, Graph<T, W>& mst);
	void findShortestPath(const T& v1, const T& v2);
	//friend ostream& operator<<(ostream& os, const Graph<T, W>& graph);	由于定义了Display函数，所以不需要定义为友元函数即可实现

};

template <typename T, typename W>
inline Graph<T, W>::Graph(int maxV) {
	numVertices = 0;
	maxVertices = maxV;
	numEdges = 0;
	adj.resize(maxV);
	for (int i = 0; i < maxV; i++) {
		adj[i].resize(maxV);
	}
}

template <typename T, typename W>
inline Graph<T, W>::Graph(int maxV, vector<T> vertex)
{
	numVertices = vertex.size();
	maxVertices = maxV;
	numEdges = 0;
	adj.resize(maxV);
	for (int i = 0; i < maxV; i++) {
		adj[i].resize(maxV);
	}
	this->vertex.resize(numVertices);
	for (int i = 0; i < numVertices; i++) {
		this->vertex[i] = vertex[i];
	}
}

template <typename T, typename W>
inline Graph<T, W>::~Graph()
{
	for (int i = 0; i < maxVertices; i++) {
		adj[i].clear();
	}
	adj.clear();
	vertex.clear();
}

template <typename T, typename W>
inline Graph<T, W>::Graph(const Graph<T, W>& other)
{
	this->maxVertices = other.maxVertices;
	this->numVertices = other.numVertices;
	this->numEdges = other.numEdges;
	this->vertex.resize(numVertices);
	for (int i = 0; i < other.numVertices; i++) {
		this->vertex[i] = other.vertex[i];
	}
	this->adj.resize(maxVertices);
	for (int i = 0; i < maxVertices; i++) {
		adj[i].resize(maxVertices);
	}
	for (int i = 0; i < other.numVertices; i++) {
		for (int j = 0; j < other.numVertices; j++) {
			this->adj[i][j] = other.adj[i][j];
		}
	}
}

template <typename T, typename W>
inline void Graph<T, W>::addVertex(T v) {
	if (numVertices < maxVertices) {
		vertex.push_back(v);
		numVertices++;
	}
	else {
		cout << "Graph is full." << endl;
	}
}

template <typename T, typename W>
inline void Graph<T, W>::addEdge(const T& v1, const T& v2, int weight) {
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

template <typename T, typename W>
inline void Graph<T, W>::addEdge(int i, int j, int weight) {
	if (i >= 0 && j >= 0) {
		adj[i][j] = weight;
		adj[j][i] = weight;
		numEdges++;
	}
	else {
		cout << "Invalid vertices" << endl;
	}
}

template<typename T, typename W>
inline void Graph<T, W>::removeEdge(int i, int j)
{
	adj[i][j] = 0;
}

template <typename T, typename W>
inline int Graph<T, W>::findIndex(const T& v) {
	for (int i = 0; i < numVertices; i++) {
		if (vertex[i] == v) {
			return i;
		}
	}
	return -1;
}

template <typename T, typename W>
inline bool Graph<T, W>::hasPath(const T& v1, const T& v2) {
	int i = findIndex(v1);
	int j = findIndex(v2);
	if (i < 0 || j < 0) {
		return false;
	}
	vector<bool> visited(numVertices, false);
	return hasPathHelper(i, j, visited);
}

template <typename T, typename W>
inline bool Graph<T, W>::hasPathHelper(int i, int j, vector<bool>& visited) {
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

template <typename T, typename W>
inline void Graph<T, W>::printAllPaths(const T& v1, const T& v2) {
	int i = findIndex(v1);
	int j = findIndex(v2);
	if (i < 0 || j < 0) {
		cout << "Invalid vertices" << endl;
		return;
	}
	vector<bool> visited(numVertices, false);
	vector<int> path;
	printAllPathsHelper(i, j, visited, path);
}

template <typename T, typename W>
inline void Graph<T, W>::printAllPathsHelper(int i, int j, vector<bool>& visited, vector<int>& path) {
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


template <typename T, typename W>
inline int Graph<T, W>::findParent(vector<int>& parent, int u)
{
	if (parent[u] == u)
	{
		return u;
	}

	return findParent(parent, parent[u]);
}

template<typename T, typename W>
inline void Graph<T, W>::findShortestPathHelper(int i, int j, vector<bool>& visited, vector<int>& path, vector<int>& shortest_path, W& weight)
{
	visited[i] = true;
	path.push_back(i);
	if (i == j) {
		W sum_weight = 0;
		for (int k = 0; k < path.size()-1; k++) {
			sum_weight += adj[path[k]][path[k + 1]];
		}
		if (sum_weight < weight) {
			weight = sum_weight;
			shortest_path = path;
		}
	}
	else {
		for (int k = 0; k < numVertices; k++) {
			if (adj[i][k] != 0 && !visited[k]) {
				findShortestPathHelper(k, j, visited, path, shortest_path, weight);
			}
		}
	}
	visited[i] = false;
	path.pop_back();
}

template <typename T, typename W>
inline void Graph<T, W>::Display() const{
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

template <typename T, typename W>
Graph<T, W>& Graph<T, W>::operator=(const Graph<T, W>& other) {
	if (this != &other) {
		this->maxVertices = other.maxVertices;
		this->numVertices = other.numVertices;
		this->numEdges = other.numEdges;
		this->vertex.resize(numVertices);
		for (int i = 0; i < other.numVertices; i++) {
			this->vertex[i] = other.vertex[i];
		}
		this->adj.resize(maxVertices);
		for (int i = 0; i < maxVertices; i++) {
			adj[i].resize(maxVertices);
		}
		for (int i = 0; i < other.numVertices; i++) {
			for (int j = 0; j < other.numVertices; j++) {
				this->adj[i][j] = other.adj[i][j];
			}
		}
	}
	return *this;
}

template <typename T, typename W>
inline Graph<T, W> Graph<T, W>::Kruskal()
{
	Graph<T, W> mst(maxVertices, vertex);
	//初始化一个边的列表并将其按权值排序
	vector<pair<int, pair<int, int>>> edges;
	for (int i = 0; i < numVertices; i++)
	{
		for (int j = i + 1; j < numVertices; j++)
		{
			if (adj[i][j] != 0)
			{
				edges.push_back(make_pair(adj[i][j], make_pair(i, j)));
			}
		}
	}
	sort(edges.begin(), edges.end());
	//定义一个parent数组来存储每个顶点的根节点，来实现并查集合并
	vector<int> parent(numVertices);
	for (int i = 0; i < numVertices; i++)
	{
		parent[i] = i;
	}
	for (int i = 0; i < edges.size(); i++)
	{
		int weight = edges[i].first;
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		int parentU = findParent(parent, u);
		int parentV = findParent(parent, v);
		if (parentU != parentV)
		{
			mst.addEdge(u, v, weight);
			parent[parentU] = parentV;
		}
	}
	return mst;
}

template <typename T, typename W>
inline Graph<T, W> Graph<T, W>::Prim()
{
	Graph<T, W> mst(numVertices);
	if (numVertices == 0)	return mst;
	vector<bool> visited(numVertices, false);
	visited[0] = true;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	mst.addVertex(vertex[0]);
	for (int j = 0; j < numVertices; j++) {
		if (adj[0][j] != 0) {
			pq.push({ adj[0][j], j });
		}
	}
	int from = 0;
	for (int i = 1; i < numVertices; i++) {
		while (!pq.empty() && visited[pq.top().second]) {
			pq.pop();
		}
		if (pq.empty()) {
			break;
		}
		int src = pq.top().second;
		int weight = pq.top().first;
		pq.pop();
		visited[src] = true;
		mst.addVertex(vertex[src]);
		mst.addEdge(vertex[from], vertex[src], weight);
		from = src;
		for (int j = 0; j < numVertices; j++) {
			if (adj[src][j] != 0 && !visited[j]) {
				pq.push({ adj[src][j], j });
			}
		}
	}
	return mst;
}

template<typename T, typename W>
inline Graph<T, W> Graph<T, W>::breakCircle()
{
	Graph<T, W> mst(*this);
	vector<bool> visited(numVertices, false);
	while (true) {
		fill(visited.begin(), visited.end(), false);
		vector<int> circle;
		for (int i = 0; i < numVertices; i++) {
			if (!visited[i] && findCircle(i, visited, circle, mst)) {
				break;
			}
			circle.clear();
		}
		if (circle.empty()) {
			break;
		}
	}
	return mst;
}

template<typename T, typename W>
inline bool Graph<T, W>::findCircle(int v, vector<bool>& visited, vector<int>& circle, Graph<T, W>& mst)
{
	visited[v] = true;
	circle.push_back(v);
	for (int i = 0; i < numVertices; i++) {
		if (mst.adj[v][i] != 0) {
			if (!visited[i]) {
				if (findCircle(i, visited, circle, mst)) {
					return true;
				}
			}
			else if (i != circle[circle.size() - 2]) {
				vector<int> edgeWeights;
				int maxIndex = -1;
				for (int j = circle.size() - 1; j > 0; j--) {
					int u = circle[j - 1], w = circle[j];
					if (mst.adj[u][w] != 0) {
						edgeWeights.push_back(mst.adj[u][w]);
						if (maxIndex == -1 || mst.adj[u][w] > edgeWeights[maxIndex]) {
							maxIndex = edgeWeights.size() - 1;
						}
					}
				}
				// 从路径中删除最大权值的边
				int k = 0;
				for (int j = circle.size() - 1; j > 0; j--) {
					int u = circle[j - 1], w = circle[j];
					if (mst.adj[u][w] != 0) {
						if (k == maxIndex) {
							mst.removeEdge(u, w);
							mst.removeEdge(w, u);
							break;
						}
						k++;
					}
				}
				return true;
			}
		}
	}
	circle.pop_back();
	return false;
}

template<typename T, typename W>
inline void Graph<T, W>::findShortestPath(const T& v1, const T& v2)
{
	int i = findIndex(v1);
	int j = findIndex(v2);
	if (i < 0 || j < 0) {
		cout << "Invalid vertices" << endl;
		return;
	}
	vector<bool> visited(numVertices, false);
	vector<int> path;
	vector<int> shortest_path;
	W weight = 0x3f3f3f3f;
	findShortestPathHelper(i, j, visited, path, shortest_path, weight);
	cout << "Shortest Path: ";
	for (int k = 0; k < shortest_path.size(); k++) {
		cout << vertex[shortest_path[k]] << " ";
	}
	cout << endl << "Shortest Weight: " << weight << endl;
}


template <typename T, typename W>
ostream& operator<<(ostream& os, const Graph<T, W>& graph) {
	graph.Display();
	return os;
}
