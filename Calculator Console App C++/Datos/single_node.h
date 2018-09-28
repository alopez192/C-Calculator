#pragma once

#pragma once

template <class T>
class single_node
{
	T data;
	single_node* next;
public:
	single_node(T data);
	single_node(T data, single_node* next);
	void set_next(single_node* next);
	single_node* get_next();
	T get_data();
	~single_node();
};

template <class T>
single_node<T>::single_node(T data)
{
	this->data = data;
	next = nullptr;
}

template <class T>
single_node<T>::single_node(T data, single_node* next)
{
	this->data = data;
	this->next = next;
}

template <class T>
void single_node<T>::set_next(single_node* next)
{
	this->next = next;
}

template <class T>
single_node<T>* single_node<T>::get_next()
{
	return next;
}

template <class T>
T single_node<T>::get_data()
{
	return data;
}

template <class T>
single_node<T>::~single_node() {}