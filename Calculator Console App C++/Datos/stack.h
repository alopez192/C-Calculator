#pragma once
#include "single_node.h"
#include <iostream>
using namespace std;

template <class T>
class stack
{
	single_node<T>* top;
	int count;
public:
	stack();
	~stack();
	void push(T data);
	T pop();
	T peek();
	bool is_empty();
	void print() const;
	int size() const;
	void clear();
};


template <class T>
stack<T>::stack()
{
	this->top = nullptr;
	this->count = 0;
}

template <class T>
stack<T>::~stack()
{
	while (!is_empty())
	{
		pop();
	}
	this->top = nullptr;
}

template <class T>
void stack<T>::push(T data)
{
	auto* new_node = new single_node<T>(data, this->top);
	this->top = new_node;
	++count;
}

template <class T>
T stack<T>::pop()
{
	if (!is_empty()) {
		single_node<T>* aux_top = this->top;
		T top_data = aux_top->get_data();
		this->top = aux_top->get_next();;
		--count;
		delete aux_top;
		return top_data;
	}

	throw new exception("No elements to pop!");
}

template <class T>
T stack<T>::peek()
{
	if (!is_empty()){
		return this->top->get_data();
	}
	throw new exception("No elements to pop!");
}

template <class T>
bool stack<T>::is_empty()
{
	return this->count == 0;
}

template <class T>
void stack<T>::print() const
{
	single_node<T>* aux_top = this->top;
	while (aux_top != nullptr) {
		cout << aux_top->get_data() << endl;
		aux_top = aux_top->get_next();
	}
}

template <class T>
int stack<T>::size() const
{
	return this->count;
}

template <class T>
void stack<T>::clear()
{
	while (!is_empty())
	{
		pop();
	}
}
