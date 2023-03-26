#pragma once
#include <queue>
#include <stack>
#include <map>
using namespace std;


template <class T>
class Node;

int max(int x, int y) { return (x > y ? x : y); }

template <class T>
void Show(Node<T>* node) {
	cout << node->val << " ";
}

template <class T>
class Node {
public:
	T val;
	Node<T>* left;
	Node<T>* right;

public:
	Node() {
		left = nullptr;
		right = nullptr;
	}
	Node(T elem) {
		val = elem;
		left = nullptr;
		right = nullptr;
	}
	~Node() {
		if (!left) {
			delete left;
		}		
		if (!right) {
			delete right;
		}
	}
	bool isLeaf() const{
		return left == nullptr && right == nullptr;
	}
	int depth() const {
		int l_depth = 0;
		int r_depth = 0;

		if (left) {
			l_depth = left->depth();
		}		
		if (right) {
			r_depth = right->depth();
		}
		return max(l_depth, r_depth) + 1;
	}
	int count() const {
		int l_count = 0;
		int r_count = 0;

		if (left) {
			l_count = left->count();
		}
		if (right) {
			r_count = right->count();
		}
		return l_count + r_count + 1;
	}

	void preOrderVisit() {
		Show(this);
		if (left) left->preOrderVisit();
		if (right) right->preOrderVisit();
	}

	void inOrderVisit() {
		if (left) left->inOrderVisit();
		Show(this);
		if (right) right->inOrderVisit();
	}

	void postOrderVisit() {
		if (left) left->postOrderVisit();
		if (right) right->postOrderVisit();
		Show(this);
	}

	void levelOrderVisit() {
		queue<Node*> node_queue;
		node_queue.push(this);
		while (!node_queue.empty()) {
			Node<T>* node = node_queue.front();
			node_queue.pop();
			if (node->left) {
				node_queue.push(node->left);
			}
			if (node->right) {
				node_queue.push(node->right);
			}
			Show(node);
		}
	}



	void invert() {
		if (left) {
			left->invert();
		}		
		if (right) {
			right->invert();
		}

		Node<T>* node = left;
		left = right;
		right = node;
	}
};

template <class T>
class BinaryTree {
private:
	Node<T>* _root;

private:
	Node<T>* create(map<int, T>& tree, int i) {
		if (tree.find(i) == tree.end()) {
			return nullptr;
		}

		Node<T>* node = new Node<T>(tree[i]);
		node->left = create(tree, i * 2);
		node->right = create(tree, i * 2 + 1);
		return node;
	}

	void destroyTree(Node<T>* node) {
		if (node != nullptr) {
			destroyTree(node->left);
			destroyTree(node->right);
			delete node;
		}
	}
	int HeightChildSiblingHelper(const Node<T> *r) const;

	int countLeafHelper(Node<T>* node){
		if(!node) return 0;
		if(node->left==nullptr && node->right==nullptr) return 1;
		return countLeafHelper(node->left) + countLeafHelper(node->right);
	}
public:
	BinaryTree(): _root(nullptr) {}
	BinaryTree(map<int, T>& tree) { _root = create(tree, 1); }
	~BinaryTree() { destroyTree(_root); }
	int HeightChildSibling() const;
	int Degree() const;
	int getDepth() {
		if (!_root) return 0;
		return _root->count();
	}
	int count() {
		if (!_root) return 0;
		return _root->count();
	}
	int countLeaf(){ return countLeafHelper(_root); }
	void preOrderVisit() { if (_root) _root->preOrderVisit(); }
	void inOrderVisit() { if (_root) _root->inOrderVisit(); }
	void inOrderTraversal() {
		stack<Node<T>*> helper;
		Node<T>* node = _root;
		while (!helper.empty()||node){
			while(node){
				helper.push(node);
				node = node->left;
			}
			node = helper.top();
			helper.pop();
			cout << node->val << " ";
			node = node->right;
		}
	}
	void postOrderVisit() { if (_root) _root->postOrderVisit(); }
	void invert() { if (_root) _root->invert(); }
};

template <class T>
int BinaryTree<T>::HeightChildSiblingHelper(const Node<T> *r) const	{
	if(r == NULL) return 0;
	else{
		int heightChild, heightSibling;
		heightChild = HeightChildSiblingHelper(r->left);
		heightSibling = HeightChildSiblingHelper(r->right);
		if( heightChild+1 > heightSibling ) return heightChild+1;
		return heightSibling;
	}
}

template <class T>
int BinaryTree<T>::HeightChildSibling() const {
	// 求孩子兄弟表示法的树的高度
	return HeightChildSibling(_root);
} 
