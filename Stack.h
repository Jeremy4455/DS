#pragma once
#include <string>
#define STACK_CAPACITY 20

void error(string msg) {
	cout << "error: " << msg << endl;
}

template <class T>
class Stack{
private:
	T* _stack;
	int _top;
public:
	Stack() {
		_stack = new T[STACK_CAPACITY];
		_top = -1;
	}	
	Stack(const T* e, int length) {
		_top = -1;
		_stack = new T[STACK_CAPACITY];
		if (length > STACK_CAPACITY) length = STACK_CAPACITY;
		for (int i = 0; i < length - 1; i++) {
			_stack[i] = e[i];
			_top++;
		}
	}
	Stack(const Stack<T>& A) {
		_stack = new T[STACK_CAPACITY];
		this->_top = A._top;
		for (int i = 0; i < A._top+1; i++) {
			_stack[i] = A._stack[i];
		}
	}
	~Stack() {
		_top = -1;
	}
	bool isEmpty()const {
		return _top < 0;
	}
	bool isFull()const {
		return _top >= STACK_CAPACITY;
	}
	int size() {
		return _top + 1;
	}
	T top() {
		if (isEmpty()) {
			error("underflow");
			exit(1);
		}
		return _stack[_top];
	}

	void push(T e) {
		if (isFull()) {
			error("overflow");
			exit(1);
		}
		_stack[_top++] = e;
	}

	T pop() {
		if (isEmpty()) {
			error("underflow");
			exit(1);
		}
		return _stack[_top--];
	}


};