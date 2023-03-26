#pragma once
#include <iostream>
using namespace std;
#define ERROR_RET 0xEFEFEFEF
template <class T>
struct Node{
	T val;
	Node<T>* next;
};

template <class T>
class LinkedList
{
private:
	Node<T>* _head;
public:
	LinkedList() {
		_head = NULL;
	}

	LinkedList(const T* A, int length) {
		for (int i = 0; i < length; i++) {
			insert(i, A[i]);
		}
	}

	~LinkedList() {
		while (_head != NULL) {
			Node<T>* tmp = _head;
			_head = _head->next;
			delete tmp;
		}
	}

	int size()const {
		int count = 0;
		Node<T>* tmp = _head;
		while (tmp!=NULL)
		{
			count++;
			tmp = tmp->next;
		}
		return count;
	}

	bool isEmpty() const {
		return _head == NULL;
	}

	Node<T>* firstNode()const {
		return _head;
	}

	Node<T>* lastNode()const {
		if (_head == NULL) {
			return NULL;
		}

		Node<T>* tmp = _head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		return tmp;
	}

	Node<T>* getNode(int pos) const{
		if (pos < 0 || _head == NULL) {
			return NULL;
		}
		int i = 0;
		Node<T>* tmp=_head;
		while (tmp->next != NULL && i < pos) {
			i++;
			tmp = tmp->next;
		}
		return tmp;
	}

	Node<T>* findNode(T e)const {
		Node<T>* tmp = _head;
		while (tmp != NULL){
			if (tmp->val == e) {
				return tmp;
			}
			tmp = tmp->next;
		}
		return NULL;
	}

	T getValue(int pos) const {
		Node<T>* node = getNode(pos);
		if (node != NULL) {
			return node->val;
		}
		else {
			return ERROR_RET;
		}
	}

	void setValue(int pos, T e) {
		Node<T>* node = getNode(pos);
		if (node != NULL) {
			node->val = e;
		}
		else {
			cerr << "Wrong position!" << endl;
		}
	}

	void insert(int pos, T e) {
		Node<T>* node = new Node<T>;
		node->val = e;
		if (pos <= 0 || _head == NULL) {
			node->next = _head;
			_head = node;
			return;
		}
		int i = 0;
		Node<T>* tmp = _head;
		while (tmp->next != NULL && i < pos - 1) {
			tmp = tmp->next;
			i++;
		}
		node->next = tmp->next;
		tmp->next = node;
		return;
	}

	void remove(int pos) {
		if (pos < 0 || _head == NULL) {
			cerr<<"wrong position";
			exit(1);
		}
		if (pos == 0) {
			Node<T>* tmp = _head;
			_head = _head->next;
			delete tmp;
			return;
		}
		int i = 0;
		Node<T>* tmp = _head;
		while (tmp->next != NULL && i < pos - 1) {
			tmp = tmp->next;
			i++;
		}
		if (tmp != NULL) {
			Node<T>* node = tmp->next;
			if (node == NULL) {
				cerr << "wrong position";
				exit(1);
			}
			else {
				tmp->next = node->next;
				delete node;
				return;
			}
		}
	}
	
	void sort() {
		Node<T> newHead;
		Node<T>* tmpHead = &newHead;
		tmpHead->next = NULL;
		while (_head != NULL) {
			int min = _head->val;
			Node<T>* preMinNode = NULL;
			Node<T>* tmpNode = _head;
			while (tmpNode->next != NULL) {
				Node<T>* node = tmpNode->next;
				if (min > node->val) {
					preMinNode = tmpNode;
					min = node->val;
				}
				tmpNode = node;
			}
			if (preMinNode == NULL) {
				tmpHead->next = _head;
				_head = _head->next;
			}
			else {
				Node<T>* node = preMinNode->next;
				tmpHead->next = node;
				preMinNode->next = node->next;
			}
			tmpHead = tmpHead->next;
			tmpHead->next = NULL;
		}
		_head = newHead.next;
	}

	friend ostream& operator<<(ostream& out, const LinkedList& A) {
		Node<T>* tmp = A._head;
		while (tmp != NULL) {
			if(tmp->next == NULL) out << tmp->val;
			else out << tmp->val << "->";
			tmp = tmp->next;
		}
		delete tmp;
		return out;
	}

	void reverse() {
		if (_head == NULL || _head->next == NULL) {
			return;
		}
		Node<T>* p = _head;
		Node<T>* q = _head->next;
		Node<T>* r=new Node<T>;
		_head->next = NULL;
		while (q != NULL) {
			r = q->next;
			q->next = p;
			p = q;
			q = r;
		}
		_head = p;
	}
};

