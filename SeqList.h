#pragma once
#define DEFAULT_CAPACITY 10
#include <stdlib.h>
#include <iostream>
using namespace std;
template <class T>
class SeqList
{
private:
	T* _elems;
	int _maxsize;
	int _size;
private:
	void copyFrom(T const* A, int low, int high) {
		_size = high + 1 - low;
		for (int i = 0; i < _size; i++) _elems[i] = A[low + i];
	}

	void expand() {
		_maxsize *= 2;
		int* oldelems = _elems;
		_elems = new T[_maxsize];
		for (int i = 0; i < _size; i++) {
			_elems[i] = oldelems[i];
		}
		delete[] oldelems;
	}

	void shrink() {
		_maxsize /= 2;
		int* oldelems = _elems;
		_elems = new T[_maxsize];
		for (int i = 0; i < _size; i++) {
			_elems[i] = oldelems[i];
		}
		delete[] oldelems;
	}

	void exchange(int a, int b) {
		T tmp = _elems[a];
		_elems[a] = _elems[b];
		_elems[b] = tmp;
	}

	int find(T e, int low, int high) {
		if (high > _size - 1) {
			high = _size - 1;
		}
		for (int i = low; i <= high; i++) {
			if (_elems[i] == e) {
				return i;
			}
		}
		return -1;
	}

public:
	SeqList(int c = DEFAULT_CAPACITY) {
		_maxsize = c;
		_elems = new T[_maxsize];
		_size = 0;
	}

	SeqList(T const* A, int size) {
		_maxsize = size + 1;
		_elems = new T[_maxsize];
		copyFrom(A, 0, size - 1);
	}

	SeqList(T const* A, int low, int high) {
		_maxsize = high + 1 - low + 1;
		_elems = new T[_maxsize];
		copyFrom(A, low, high);
	}

	SeqList(const SeqList& A) {
		_maxsize = A.size() + 1;
		_size = A.size();
		_elems = new T[_maxsize];
		copyFrom(A._elems, 0, A.size()-1);
	}

	~SeqList() {
		delete[] _elems;
	}

	T& operator[](int i) const {
		return _elems[i];
	}

	int size() const {
		return _size;
	}

	bool isEmpty()const { return _size == 0; }

	bool isOrdered()const {
		for (int i = 1; i < _size; i++) {
			if (_elems[i - 1] > _elems[i])
				return false;
		}
		return true;
	}

	int find(T e) const {
		return find(e, 0, _size - 1);
	}

	void del(T e) {
		remove(find(e));
	}

	void insert(T e, int pos) {
		if (pos > _size) {
			pos = _size;
		}
		if (_size + 1 > _maxsize) {
			expand();
		}
		for (int i = _size - 1; i >= pos; i--) {
			_elems[i + 1] = _elems[i];
		}
		_elems[pos] = e;
		_size++;
	}

	void remove(int low, int high) {
		if (high > _size-1) {
			high = _size-1;
		}

		int delta = high + 1 - low;
		for (int i = high + 1; i < _size; i++) _elems[i - delta] = _elems[i];
		_size -= delta;
		if (_size < _maxsize / 2.0) {
			shrink();
		}
	}
	void remove(int pos) {
		remove(pos, pos);
	}

	T pop() {
		int last = _elems[_size - 1];
		remove(_size - 1);
		return last;
	}

	void append(T e) {
		insert(e, _size);
	}

	void sort() {
		if (isOrdered() == true) return;
		for (int i = 0; i < _size - 1; i++) {
			bool flag = true;
			for (int j = 0; j < _size - i - 1; j++) {
				if (_elems[j] > _elems[j + 1]) {
					exchange(j, j + 1);
					flag = false;
				}
			}
			if (flag) break;
		}
	}

	void shuffle() {
		for (int i = _size; i > 0; i--) {
			exchange(i - 1, rand() % i);
		}
	}

	friend ostream &operator<<(ostream &out, const SeqList& A) {
		out << "[";
		for (int i = 0; i < A.size()-1; i++) out << A[i] << ", ";
		out << A[A.size()-1] << "]";
		return out;
	}
};

