#pragma once
#include "ElemNode.h"
#include <iostream>
#include <math.h>
using namespace std;


template <class ElemType>
class UFSets {
protected:
	ElemNode<ElemType> *sets;
	int size;
	int Find(ElemType e) const;			//查找元素e所在根
public:
	UFSets(ElemType es[], int n);		//构造函数
	virtual ~UFSets();					//析构函数
	ElemType GetElem(int p) const;		//根据指定下标p取元素值
	int GetOrder(ElemType e) const;		//根据元素值取下标
	void Union(ElemType a, ElemType b); //合并a和b所在等价类
	bool Differ(ElemType a, ElemType b);//判断元素a和b是否在一个等价类
	UFSets(const UFSets<ElemType>& s);
	UFSets<ElemType>& operator =(const UFSets<ElemType>& s);
	friend ostream& operator<<(ostream& os, const UFSets<ElemType>& s);
};

template<class ElemType>
inline int UFSets<ElemType>::Find(ElemType e) const
{
	int p = 0;
	while (p < size && sets[p].data != e)
		p++;
	if (p == size) {
		return -1;
	}
	while (sets[p].parent > -1)
		p = sets[p].parent;
	return p;
}

template<class ElemType>
inline UFSets<ElemType>::UFSets(ElemType es[], int n)
{
	size = n;
	sets = new ElemNode<ElemType>[size];
	for (int i = 0; i < size; i++) {
		sets[i].data = es[i];
		sets[i].parent = -1;

	}
}

template<class ElemType>
inline UFSets<ElemType>::~UFSets()
{
	size = 0;
	delete[] sets;
}

template<class ElemType>
inline ElemType UFSets<ElemType>::GetElem(int p) const
{
	if (p > size - 1 || p < 0) {
		cerr << "invalid argument" << endl;
	}
	return sets[p].data;
}

template<class ElemType>
inline int UFSets<ElemType>::GetOrder(ElemType e) const
{
	int p = 0;
	while (p < size && sets[p].data != e)
		p++;
	if (p == size) {
		return -1;
	}
	return p;
}

template<class ElemType>
inline bool UFSets<ElemType>::Differ(ElemType a, ElemType b)
{
	if(Find(a) != -1 && Find(b) != -1)
		return Find(a) == Find(b);
	return false;
}

template<class ElemType>
inline UFSets<ElemType>::UFSets(const UFSets<ElemType>& s)
{
	size = s.size;
	sets = new ElemNode<ElemType>[size];
	for (int i = 0; i < size; i++) {
		sets[i].data = s.sets[i].data;
		sets[i].parent = s.sets[i].parent;
	}
}

template<class ElemType>
inline UFSets<ElemType>& UFSets<ElemType>::operator=(const UFSets<ElemType>& s)
{
	size = s.size;
	sets = new ElemNode<ElemType>[size];
	for (int i = 0; i < size; i++) {
		sets[i].data = s.sets[i].data;
		sets[i].parent = s.sets[i].parent;
	}
	return *this;
}

template<class ElemType>
inline void UFSets<ElemType>::Union(ElemType a, ElemType b)
{
	/// <summary>
	/// 根节点的parent存储树的高度的相反数
	/// </summary>
	int rootA = Find(a);
	int rootB = Find(b);
	if (rootA == rootB || rootA == -1 || rootB == -1) {
		return;
	}
	// 如果rootA的高度更高，就把rootB的parent设为rootA，然后rootA的高度取rootB的高度+1和rootA原本高度的最大值
	if (sets[rootA].parent > sets[rootB].parent) {
		sets[rootB].parent = min(sets[rootB].parent, sets[rootA].parent-1);
		sets[rootA].parent = rootB;
	}
	else {
		sets[rootA].parent = min(sets[rootA].parent, sets[rootB].parent - 1);
		sets[rootB].parent = rootA;
	}

}

