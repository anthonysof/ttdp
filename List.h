#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

#include "ListNode.h"

template <typename T>
class List
{
	public:
		List();
		~List();
		void print();		//τυπώνει τα περιεχόμενα της λίστας
		int search(T& key);		//επιστρέφει την θέση του key στην λίστα, αλλιώς -1
		bool isEmpty();		//επιστρέφει true ή false αν η λίστα είναι άδεια ή όχι
		int insertStart(const T& dataIn);
		int insertEnd(const T& dataIn);
		int insertPos(const T& dataIn, int pos); //check!!!!
		int deleteStart(T&);
		int deletePos(T&, int pos);
		int length();
		bool findElem(int pos, T& elem);
	private:
		ListNode<T> *head;
		ListNode<T> *tail;
	
};

template <typename T>
List<T>::List()
{
	head = NULL;
	tail = NULL;
}

template <typename T>
List<T>::~List()
{
	if (!isEmpty()){
		ListNode<T> *current = head;
		ListNode<T> *temp;
		while(current != 0)
		{
			temp = current;
			current = current->next;
			delete temp;
		}
	}
}

template <typename T>
bool List<T>::isEmpty()
{
	if(head == NULL && tail == NULL)
		return 1;
	else
		return 0;
}

template <typename T>
int List<T>::insertStart(const T& dataIn)
{
	if(isEmpty())
	{
		ListNode<T> *newNode = new ListNode<T>(dataIn);
		head = newNode;
		tail = newNode;
		return 1;
	}else
	{
		ListNode<T> *newNode = new ListNode<T>(dataIn);
		newNode->next = head;
		head = newNode;
		return 1;
	}
}

template <typename T>
int List<T>::insertEnd(const T& dataIn)
{
	if(isEmpty())
	{
		ListNode<T> *newNode = new ListNode<T>(dataIn);
		head = newNode;
		tail = newNode;
		return 1;
	}else
	{
		ListNode<T> *newNode = new ListNode<T>(dataIn);
		tail->next = newNode;
		tail = newNode;
		return 1;
	}
}

template <typename T>
int List<T>::insertPos(const T& dataIn, int pos)
{
	ListNode<T> *temp = head;
	if (pos < 0)
	{
		return 0;
	}
		for(int i = 1; i<pos && temp; i++)
			temp = temp->next;
		if(pos > 0 && !temp)
			return 0;
		ListNode<T> *newNode = new ListNode<T>(dataIn);
		if(pos) {
			newNode->next = temp->next;
			temp->next = newNode;
			return 1;
		}
		else
		{
			insertStart(dataIn);
			return 1;
		}
	}


template<typename T>
int List<T>::search(T& key)
{
	ListNode<T>* temp = head;
	int count = 0;
	while(temp && temp->data != key)
	{
		temp = temp->next;
		count++;
	}
	if (temp) return count;
	return -1;
}


template<typename T>
void List<T>::print()
{
	if(isEmpty())
	{
		cout<<"The List is empty"<<endl;
	}else
	{
		ListNode<T> *current = head;
		cout<<"The contents are:\n";
		while(current!=NULL)
		{
			cout<<current->data<<"->";
			current = current->next;
		}
		cout<<endl;
	}
}

template<typename T>
int List<T>::deleteStart(T& deleted)
{
	if(isEmpty())
	{
		return 0;
	}
	ListNode<T> *temp = head;
	head = head->next;
	deleted = temp->data;
	delete temp;
	return 1;
}

template<typename T>
int List<T>::deletePos(T& deleted, int pos)
{
	ListNode<T> *temp = head;
	ListNode<T> *prev = head;
	if(isEmpty() || pos > length() || pos < 0){
		return -1;
	}
	else{
		if(pos == 0)
		{
			deleteStart(deleted);
			return 0;
		}
		else
		{
			for (int i = 0; i < pos-1 && prev; i++)
				prev = prev->next;
			if(!prev || !prev->next)
				return 0;
			temp = prev->next;
			prev->next = temp->next;
				}		
			deleted = temp->data;
			delete temp;
			return 1;
	}
}
template <typename T>
int List<T>::length()
{
	int count = 0;
	ListNode<T> *temp = head;
	while(temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return count;
}

template <typename T>
bool List<T>::findElem(int pos, T& elem)
{
	if(pos < 0)
	{
		return false;
	}
	ListNode<T> *current = head;
	int count = 0;
	while(count < pos && current)
	{
		current = current->next;
		count++;
	}
	if (current){
		elem = current->data;
		return true;
	}
	return false;
}
#endif



