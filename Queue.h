#pragma once
#include <stdlib.h>
#define ERROR_RET 0xEFEFEFEF
template <class T>
class Node
{
public:
	T val;
	Node<T>* next;
	Node() {
		next = NULL;
	}
};

template <class T>
class Queue {
private:
	Node* _head;
	Node* _tail;
public:
	Queue() {
		_head = NULL;
		_tail = NULL;
	}
	~Queue() {
		while (_head != NULL) {
			Node<T>* node = _head->next;
			delete _head;
			_head = node;
		}
	}
	bool isEmpty()const {
		return _head == NULL;
	}
};