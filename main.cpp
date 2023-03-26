#include <iostream>
#include "BinaryTree.h"
using namespace std;

int main() {
	map<int, string> map;
	int n;
	cout << "输入结点个数："<< endl;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int key;
		string val;
		cin >> key >> val;
		map[key] = val;
	}
	BinaryTree<string> tree(map);
	cout << "孩子兄弟树的高度:" << endl;
	cout << tree.HeightChildSibling() << endl;
	return 0;
}