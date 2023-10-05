#pragma once

#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

class Node
{
private:
	friend class DoubleLinkedList;
	int data;
	Node* next;
	Node* prev;

public:
	Node(int data) : data(data), next(NULL), prev(NULL) {};
	~Node() {};
	friend ostream& operator<<(ostream& os, const Node& data);
};


class DoubleLinkedList
{
private:
	Node* head;
	Node* tail;
	int Size;

	void insertionSort(Node* head, bool asc);					// Insertion Sort
	void mergeSort(Node** head, bool asc);						//
	void split(Node* head, Node** front, Node** back);			// Merge Sort
	Node* merge(Node* first, Node* second, bool asc);			//	
	Node* nextNode(Node* node) const { return node->next; };	// Get next node
	Node* prevNode(Node* node) const { return node->prev; };	// Get previous node
	int getData(Node* node) const { return node->data; };		// Get data from node
	friend ostream& operator<<(ostream& os, const DoubleLinkedList& list); 

public:
	DoubleLinkedList() : head(NULL), tail(NULL), Size(0) {};
	~DoubleLinkedList() { deleteList(); };

	void push_back(int data);
	void push_front(int data);
	void insert_pos(int pos, int data);
	void sort(int type, bool asc);
	void pop_back();
	void pop_front();
	void remove_pos(int pos);
	void remove_data(int data);
	void reverse();
	void swap(int pos1, int pos2);
	bool empty();
	void deleteList();
	int size() const { return this->Size; };
	void print() const;
	void print(Node* head) const
	{
		if (head == NULL)
			cout << "NULL" << endl;
		else
			cout << head << endl;
	}
	Node* search(int data) const;
};
