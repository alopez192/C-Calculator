#pragma once
#include <iostream>
#include<string>
#include "single_node.h"
using namespace std;

template <class T>
class queue
{
	single_node<T>* front;
	single_node<T>* rear;
	int count;
public:
	queue();
	~queue();
	int size();
	void enqueue(T data);
	T dequeue();
	T peek_front();
	T peek_back();
	bool is_empty();
	void print() const;
	string to_string();
};

template <class T>
queue<T>::queue()
{
	front = rear = nullptr;
	count = 0;
}

template <class T>
queue<T>::~queue()
{
	while (!is_empty())
	{
		dequeue();
	}
	front = rear = nullptr;
	count = 0;
}

template <class T>
int queue<T>::size()
{
	return this->size();
}

template <class T>
void queue<T>::enqueue(T data)
{
	single_node<T>* new_node = new single_node<T>(data);
	if(is_empty())
	{
		this->front = this->rear = new_node;
		count++;
	}
	else
	{
		this->rear->set_next(new_node);
		this->rear = new_node;
		count++;
	}
}

template <class T>
T queue<T>::dequeue()
{
	T aux_data = front->get_data();
	single_node<T>* aux_node = front;
	front = aux_node->get_next();
	delete aux_node;
	count--;
	return aux_data;
}

template <class T>
T queue<T>::peek_front()
{
	return this->front->get_data();
}

template<class T>
inline T queue<T>::peek_back()
{
	return this->rear->get_data();
}

template <class T>
bool queue<T>::is_empty()
{
	return (this->count == 0);
}

template <class T>
void queue<T>::print() const
{
	single_node<T>* aux = front;
	while (aux != nullptr)
	{
		cout << "_" << aux->get_data();
		aux = aux->get_next();
	}
	cout << endl;
}

template <class T>
string queue<T>::to_string()
{
	stringstream str_builder;
	single_node<T>* aux = front;
	while (aux != nullptr)
	{
		str_builder << aux->get_data();
		aux = aux->get_next();
	}
	return str_builder.str();
}



