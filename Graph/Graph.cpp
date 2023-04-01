#include "Graph.h"

using namespace std;

int main() {
    Graph<string> g(5);
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");
    g.addVertex("E");
    g.addEdge("A", "B");
    g.addEdge("B", "C");
    g.addEdge("C", "D");
    g.addEdge("D", "E");
    g.addEdge("A", "E");
    cout << g;
    cout << g.hasPath("A", "C") << endl; // true
    cout << g.hasPath("A", "D") << endl; // true
    cout << g.hasPath("A", "F") << endl; // false
    cout << "All paths between vertices A and D:" << endl;
    g.printAllPaths("A", "D");
    return 0;
}

