#pragma once
#include <iostream>
using namespace std;

class expression_operator{
	char exp_operator;
	int priority_exp;
	int priority_stack;

public:
	expression_operator();
	expression_operator(char op, int priority_exp, int priority_stack);
	~expression_operator();
	void set_expresion_operator(char expresion_operator);
	void set_priority_exp(int priority_exp);
	void set_priority_stack(int priority_stack);
	char get_expresion_operator() const;
	int get_priority_exp() const;
	int get_priority_stack() const;
};