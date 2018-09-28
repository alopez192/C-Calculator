#pragma once

template <class T>
class double_linked_list_node
{
	T data;
	double_linked_list_node* next;
	double_linked_list_node* prev;

public:
	double_linked_list_node(T data);
	T get_data();
	void set_next(double_linked_list_node* next);
	void set_prev(double_linked_list_node* prev);
	void set_data(T data);
	double_linked_list_node* get_prev();
	double_linked_list_node* get_next();
	~double_linked_list_node();
};


template <class T>
double_linked_list_node<T>::double_linked_list_node(T data)
{
	this->data = data;
	this->next = nullptr;
	this->prev = nullptr;
}

template <class T>
T double_linked_list_node<T>::get_data()
{
	return data;
}

template <class T>
void double_linked_list_node<T>::set_next(double_linked_list_node *next)
{
	this->next = next;
}

template <class T>
void double_linked_list_node<T>::set_prev(double_linked_list_node *prev)
{
	this->prev = prev;
}

template <class T>
void double_linked_list_node<T>::set_data(T data)
{
	this->data = data;
}

template <class T>
double_linked_list_node<T>* double_linked_list_node<T>::get_prev()
{
	return prev;
}

template <class T>
double_linked_list_node<T>* double_linked_list_node<T>::get_next() { return next; }

template <class T>
double_linked_list_node<T>::~double_linked_list_node() {}

