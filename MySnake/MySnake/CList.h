#ifndef CLIST_H
#define CLIST_H
#include <iostream>
template <class T>
struct Node {
	T item;
	Node<T>* next;
	Node();
	Node(T, Node<T> * = nullptr);
	Node(const Node<T>&);
	Node<T>& operator=(const Node<T>&);
	~Node();
};

template <class T>
using CList = Node<T>*;
#include "CList.cpp"
#endif // !CLIST_H


