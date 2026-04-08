#pragma once

#include <iostream>
using namespace std;
template <class t >
class node {
	t data;
	node<t>* next;
node<t>* prev; public:
	node() :data(t()), next(nullptr), prev(nullptr) {}

	void setData(t x) {
		data = x;
	}
	void setNext(node<t>* c) {
		next = c;
	}
	void setPrev(node<t>* c) {
		prev = c;
	}
	t getData() {
		return data;
	}
	node<t>* getNext() {

		return next;
	}
	node<t>* getPrev() {
		return prev;
	}
}; template <class t>class DoublyLinkedList {

	node<t>* head, * tail;
int size; public:
	DoublyLinkedList() {
		head = tail = nullptr;
		size = 0;
	}
	DoublyLinkedList(const DoublyLinkedList& l) {
		size = 0;
		head = tail = nullptr;
		node<t>* current = l.head;
		if (l.head == nullptr) {
			return;
		}
		node<t>* n = new node<t>();
		n->setData(current->getData());
		head = tail = n;
		current = current->getNext();
		size++;

		while (current != nullptr) {
			node<t>* n = new node<t>();
			tail->setNext(n);
			n->setPrev(tail);
			n->setData(current->getData());
			tail = n;
			size++;
			current = current->getNext();
		}
	}
	void insertAtEnd(t d) {
		size++;
		node<t>* n = new node<t>();
		n->setData(d);
		if (head == nullptr) {
			head = tail = n;
			return;
		}
		else {
			tail->setNext(n);
			n->setPrev(tail);

			tail = n;
		}
	}
	void insertAtStart(t x) {
		size++;
		node <t>* n = new node<t>();
		n->setData(x);
		if (head == nullptr) {
			head = tail = n;
			return;
		}
		else {
			n->setNext(head);
			head->setPrev(n);
			head = n;
		}
	}
	void displayForward() {
		if (head == nullptr) {
			cout << "The list is empty";
			return;
		}
		else {
			node<t>* temp = head;
			while (temp != nullptr) {
				cout << "Data = " << temp->getData() << endl;
				temp = temp->getNext();
			}
		}
	}
	void displayBackward() {
		if (head == nullptr) {
			cout << "The list is empty";
			return;
		}
		else {
			node<t>* temp = tail;
			while (temp != nullptr) {

				cout << "Data = " << temp->getData() << endl;
				temp = temp->getPrev();
			}
		}
	}
	bool search(t data) {
		node <t>* temp = head;
		while (temp != nullptr) {
			if (data == temp->getData())
			{

				cout << "Data " << data << " is present in the list." << endl;
				cout << "This is present in the list";
				return true;

			}
			temp = temp->getNext();
		}
		cout << "The data is not present" << endl;
		return false;
	}

	int search__b(t data) {
		node <t>* temp = head;
		int count = 0;
		while (temp != nullptr) {
			
			if (data == temp->getData())
			{

				cout << "Data " << data << " is present in the list." << endl;
				cout << "This is present in the list";
				return count;

			}
			count++;
			temp = temp->getNext();
		}
		cout << "The data is not present" << endl;
		return -1;
	}
	~DoublyLinkedList() {
		node<t>* temp = tail;
		while (temp != nullptr) {
			node<t>* prev = temp->getPrev();
			delete temp;
			temp = prev;
		}
		tail = head = nullptr;
	}

	void deleteAtPosition(int pos) {
		int count = 0;
		node<t>* temp = head;
		if (pos < 0 || pos >= size) {
			cout << "Invalid position." << endl;
			return;
		}
		if (head == nullptr) {
			cout << "The list is empty " << endl;
		}
		if (pos < 0) {
			cout << "Invalid position." << endl;
			return;
		}
		if (pos == 0) {
			head = head->getNext();
			if (head != nullptr) {
				head->setPrev(nullptr);
			}
			else {

				tail = nullptr; // list became empty 
			}
			delete temp;
			size--;
			return;
		}
		while (temp != nullptr && count < pos) {
			temp = temp->getNext();
			count++;
		}
		node<t>* prevNode = temp->getPrev();
		node<t>* nextNode = temp->getNext();
		if (prevNode != nullptr) {
			prevNode->setNext(nextNode);
		}
		if (nextNode != nullptr) {
			nextNode->setPrev(prevNode);
		}
		else {
			tail = prevNode; 
		}

		size--;
		delete temp;
	}
	void deleteAtStart() {
		if (head == nullptr) {
			cout << "The List is empty";
			return;
		}
		node<t>* temp = head;
		head = head->getNext();
		delete temp;
		size--;
		if (head != nullptr) {
			head->setPrev(nullptr);
		}
		else {
			tail = nullptr;
			head = nullptr;
		}

	}
	void deleteAtEnd() {
		node<t>* n = tail;
		if (head == nullptr) {
			cout << "The list is empty";
			return;
		}
		tail = tail->getPrev();
		delete n;
		if (tail != nullptr) {
			tail->setNext(nullptr);
		}
		else {
			head = tail = nullptr;
		}
		size--;
	}
	void insertAtAnyPosition(int pos, node<t>* n) {
		if (pos < 0 || pos > size) {
			cout << "Invalid position." << endl;
			return;
		}

		if (pos == 0) {
			insertAtStart(n->getData());
			delete n;
			return;
		}

		node<t>* temp = head;
		for (int count = 0; count < pos - 1; count++) {
			temp = temp->getNext();
		}


		node<t>* nextNode = temp->getNext();

		n->setNext(nextNode);
		n->setPrev(temp);
		temp->setNext(n);

		if (nextNode != nullptr) {
			nextNode->setPrev(n);
		}
		else {
			tail = n;
		}
		size++;
	}
	bool isEmpty() {
		return head == nullptr;
	}
	DoublyLinkedList Intersection(const  DoublyLinkedList& d1) {
		DoublyLinkedList <t>Intersect;
		node<t>* temp = d1.head;
		node<t>* temp1 = head;
		if (temp1 == nullptr || temp == nullptr) {
			cout << "No insteresction";
			return Intersect;
		}

		while (temp != nullptr) {
			while (temp1 != nullptr) {
				if (temp1->getData() == temp->getData()) {
					Intersect.insertAtStart(temp1->getData());
					break;
				}
				temp1 = temp1->getNext();
			}
			temp1 = head;
			temp = temp->getNext();
		}
		return Intersect;
	}

	int getSize() {
		return size;
	}
	node<t> * getHead() { return head; }
	node<t>* getTail () { return tail; }
};
