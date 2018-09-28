#pragma once
#include <iostream>
#include "double_linked_list_node.h"
using namespace std;

template<class T>
class double_linked_list {
private:
	double_linked_list_node<T>* front;
	double_linked_list_node<T>* back;
	int size;
public:
	double_linked_list();
	double_linked_list_node<T>* get_front();
	double_linked_list_node<T>* get_back();
	int get_size() const;
	bool is_empty() const;
	void add_front(T data);
	void add_back(T data);
	void add_after(T data, int index);
	void add(T data);
	void delete_element(int index);
	double_linked_list_node<T>* find_element(T data);
	T get(int index);
	void print_forward() const;
	void print_backward() const;
	~double_linked_list();
};

template <class T>
double_linked_list<T>::double_linked_list()
{
	front = nullptr;
	back = nullptr;
	size = 0;
}

template <class T>
double_linked_list_node<T>* double_linked_list<T>::get_front()
{
	return front;
}

template <class T>
double_linked_list_node<T>* double_linked_list<T>::get_back()
{
	return back;
}

template <class T>
int double_linked_list<T>::get_size() const
{
	return size;
}

template <class T>
bool double_linked_list<T>::is_empty() const
{
	return size == 0;
}

template <class T>
void double_linked_list<T>::add_front(T data)
{
	double_linked_list_node<T>* new_node = new double_linked_list_node<T>(data);
	new_node->set_next(nullptr);
	new_node->set_prev(nullptr);

	if (front == nullptr) {
		front = back = new_node;
	}
	else {
		front->set_prev(new_node);
		new_node->set_next(front);
		front = new_node;
	}
	size += 1;
}

template <class T>
void double_linked_list<T>::add_back(T data)
{
	double_linked_list_node<T>* new_node = new double_linked_list_node<T>(data);
	new_node->set_next(nullptr);
	new_node->set_prev(nullptr);

	if (back == nullptr)
	{
		front = back = new_node;
	}
	else
	{
		back->set_next(new_node);
		new_node->set_prev(back);
		back = new_node;
	}
	size += 1;
}

template <class T>
void double_linked_list<T>::add_after(T data, int index)
{
	double_linked_list_node<T>* new_node = new double_linked_list_node<T>(data);
	if (!is_empty() && index >= 0 && index < get_size())
	{
		if (index == 0)
		{
			add_front(node);
		}
		else if (index == (get_size() - 1))
		{
			add_back(new_node);
		}
		else
		{
			bool found = false;
			int internal_index = 0;
			double_linked_list_node<T>* aux = nullptr;

			if (index < (get_size() / 2)) //is present of the first half of the list, search using front
			{
				aux = front;
				while (!found)
				{
					if (internal_index == index)
					{
						found = true;
					}
					else
					{
						internal_index++;
						aux = aux->get_next();
					}
				}
			}
			else //search using the back as the node should present on the second half
			{
				aux = back;
				internal_index = get_size() - 1;
				while (!found)
				{
					if (internal_index == index)
					{
						found = true;
					}
					else
					{
						internal_index--;
						aux = aux->get_prev();
					}
				}
			}

			if (found)
			{
				double_linked_list_node<T>* temp = aux;
				new_node->set_prev(temp);
				new_node->set_next(temp->get_next());
				aux->set_next(new_node);
				temp->get_next()->set_prev(new_node);
			}
		}
	}
}

template <class T>
void double_linked_list<T>::add(T data)
{
	add_back(data);
}

template <class T>
void double_linked_list<T>::delete_element(int index)
{
	if (!is_empty() && index >= 0 && index < get_size())
	{
		double_linked_list_node<T>* aux = nullptr;
		const int last_index = get_size() - 1;
		if (front == nullptr && back == nullptr)
			return;//escape from function 
		if (index == 0  && front != nullptr)
		{
			aux = front;
			front = aux->get_next();
			if(front != nullptr)
				front->set_prev(nullptr);
			aux = nullptr;
			--this->size;
		}
		else if (index == last_index && back != nullptr)
		{
			aux = back;
			back = aux->get_prev();
			if(back!= nullptr)
				back->set_next(nullptr);
			aux = nullptr;
			--this->size;
		}
		else
		{
			bool found = false;
			int internal_index = 0;
			double_linked_list_node<T>* aux = nullptr;

			if (index < (last_index / 2)) //is present of the first half of the list, search using front
			{
				aux = front;
				while (!found)
				{
					if (internal_index == index)
					{
						double_linked_list_node<T>* temp = aux;
						aux->get_next()->set_prev(temp->get_prev());
						aux->get_prev()->set_next(temp->get_next());
						delete temp;
						found = true;
						--this->size;
					}
					else
					{
						internal_index++;
						aux = aux->get_next();
					}
				}
			}
			else //search using the back as the node should present on the second half
			{
				aux = back;
				internal_index = get_size() - 1;
				while (!found)
				{
					if (internal_index == index)
					{
						double_linked_list_node<T>* temp = aux;
						aux->get_next()->set_prev(temp->get_prev());
						aux->get_prev()->set_next(temp->get_next());
						delete temp;
						found = true;
						--this->size;
					}
					else
					{
						internal_index--;
						aux = aux->get_prev();
					}
				}
			}
		}
	}
}

template <class T>
double_linked_list_node<T>* double_linked_list<T>::find_element(T data)
{
	double_linked_list_node<T>* aux = nullptr;
	if (!is_empty())
	{
		if (front->get_data() == data)
		{
			return front;
		}
		if (back->get_data() == data)
		{
			return back;
		}

		bool found = false;
		aux = front;
		while (!found && aux != nullptr)
		{
			if (aux->get_data() == data)
			{
				found = true;
			}
			else
			{
				aux = aux->get_next();
			}
		}
		return aux;
	}
	return aux;
}

template <class T>
T double_linked_list<T>::get(int index)
{
	double_linked_list_node<T>* node = nullptr;

	if (!is_empty() && index >= 0 && index < get_size())
	{
		const auto last_index = size - 1;
		if (index == 0)
		{
			node = front;
		}
		if (index == last_index)
		{
			node = back;
		}
		else
		{
			bool found = false;
			int internal_index = 0;
			double_linked_list_node<T>* aux = nullptr;

			if (index < (get_size() / 2)) //is present of the first half of the list, search using front
			{
				aux = front;
				while (!found)
				{
					if (internal_index == index)
					{
						node = aux;
						found = true;
					}
					else
					{
						internal_index++;
						aux = aux->get_next();
					}
				}
			}
			else //search using the back as the node should present on the second half
			{
				aux = back;
				internal_index = get_size() - 1;
				while (!found)
				{
					if (internal_index == index)
					{
						node = aux;
						found = true;
					}
					else
					{
						internal_index--;
						aux = aux->get_prev();
					}
				}
			}
		}
	}
	return node->get_data();
}

template <class T>
void double_linked_list<T>::print_forward() const
{
	double_linked_list_node<T>* aux = front;
	int index = 0;
	while (aux != nullptr)
	{
		//cout << "[" << index++ << "] : " << aux->get_data() << endl;
		cout << "[ " << aux->get_data() << " ]";
		aux = aux->get_next();
	}
}

template <class T>
void double_linked_list<T>::print_backward() const
{
	double_linked_list_node<T>* aux = back;
	int index = get_size() - 1;
	while (aux != nullptr)
	{
		//cout << "[" << index-- << "] :  " << aux->get_data() << endl;
		cout<< "[ "<<aux->get_data() <<" ]";
		aux = aux->get_prev();
	}
}

template <class T>
double_linked_list<T>::~double_linked_list()
{
	double_linked_list_node<T>* aux = front;
	while (aux != nullptr)
	{
		double_linked_list_node<T>* next = aux->get_next();
		delete aux;
		aux = next;
	}
	front = back = nullptr;
}