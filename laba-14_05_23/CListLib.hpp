#pragma once
#include <iostream>
using namespace std;
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED   "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[33m"
#define BLUE "\033[34m"
template<typename T>
class TListNode {
private:
	TListNode* previus;
	TListNode* next;
	T node;
public:
	TListNode() {
		next = nullptr;
		previus = nullptr;
	}
	TListNode(T &_node, TListNode*_previus = nullptr, TListNode*_next = nullptr) {
		node = _node;
		previus = _previus;
		next = _next;
	}
	TListNode(TListNode&tmp) {
		previus = tmp.previus;
		node = tmp.node;
		next = tmp.next;
	}
	~TListNode() {}
	T& getNode() { return node; }
	TListNode& getPrevius() { return *previus; }
	TListNode* getPreviusPtr() { return previus; }
	TListNode& getNext() { return *next; }
	TListNode* getNextPtr() { return next; }
	void setNext(TListNode* _next) { next = _next; }
	void setPrevius(TListNode* _previus) { previus = _previus; }
};



template<typename T>
class TList {
public:
	int count;
	TListNode<T>* Root;
	TListNode<T>* Last;
public:
	TList():Root(nullptr),count(0),Last(nullptr) {}
	TList(TList&tmp) :Root(nullptr), count(0), Last(nullptr) {}
	~TList() {
		TListNode<T>* tmp = Last;
		while (tmp->getPreviusPtr()!=nullptr) {
			tmp = tmp->getPreviusPtr();
			//if (tmp->getNode() == NULL) { cout << "err" << endl; }
			//(tmp->getNext()).~TListNode();
			delete &(tmp->getNext());
		}
		Root->~TListNode();
	}
	void add(T& tmp) {
		cout << "add"<<endl;
		if (Root != nullptr && Last != nullptr) {
			cout << "add1" << endl;
			TListNode<T>* tmpNode = new TListNode<T>(tmp,Last);
			Last = tmpNode;
			Last->getPreviusPtr()->setNext(tmpNode);
			count++;
		}
		else {
			if (Root == nullptr) {
				TListNode<T>* tmpNode = new TListNode<T>(tmp);
				Root = tmpNode;
				count++;
			}
			else {
				if (Last == nullptr) {
					TListNode<T>* tmpNode = new TListNode<T>(tmp,Root);
					Last = tmpNode;
					Last->getPreviusPtr()->setNext(tmpNode);
					count++;
				}
			}
		}
	}
	void print() {
		TListNode<T>* tmp = Root;
		if (tmp != nullptr){
			cout << tmp->getNode() << endl;
		while (tmp->getNextPtr() != nullptr) {
			tmp = tmp->getNextPtr();
			cout << tmp->getNode() << endl;
		}
		}
	}
	

};
