#pragma once
#include <string>
#include <iostream>
#include "double_linked_list.h"
#include "expression_operator.h"
#include "stack.h"
#include "queue.h"
#include "digit.h"
using namespace std;

class expression_handler
{
	string infix_expression;
	stack<digit>* working_stack;
	queue<digit>* postfix_expression;
	queue<digit>* normalized_infix_expression;
	expression_operator get_expression_operator(char exp_operator) const;
	bool int_try_parse(string val, int& num) const;
	static bool is_operator(string value);
	double execute_operation(char exp_operator, double value_one, double value_two) const;

public:
	expression_handler(string infix_expression);
	~expression_handler();
	void set_infix_expression(string infix_expression);
	string get_infix_expression() const;
	char get_expression_sign(char prev_exp_operator, char current_exp_operator) const;
	queue<digit>& get_postfix_expression() const;
	queue<digit>& get_normalized_expression() const;
	void clean_expression(string infix_expression);
	void create_postfix_expression() const;
	double evaluate_expresion();
	void print_postfix_expresion() const;
};