#include "Graph.h"

using namespace std;

int main() {
    vector<string> v = { "A", "B", "C", "D", "E", "F" };
    Graph<string, int> g(6, v);
    g.addEdge("A", "B", 4);
    g.addEdge("A", "F", 2);
    g.addEdge("B", "C", 6);
    g.addEdge("B", "F", 5);
    g.addEdge("C", "D", 3);
    g.addEdge("C", "E", 1);
    g.addEdge("C", "F", 3);
    g.addEdge("D", "E", 7);
    g.addEdge("E", "F", 8);
    cout << g;
    cout << g.hasPath("A", "C") << endl;
    cout << g.hasPath("A", "D") << endl;
    cout << g.hasPath("A", "F") << endl;
    cout << "All paths between vertices A and D:" << endl;
    g.printAllPaths("A", "D");
    cout << g.Kruskal();
    cout << g.Prim();
    return 0;
}

