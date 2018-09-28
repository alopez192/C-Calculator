#pragma once
#include <string>
#include "double_linked_list.h"
#include "expression_operator.h"
#include "stack.h"
#include "queue.h"
#include"digit.h"
using namespace std;

class expression_handler
{
	string infix_expression;
	string exp_pos="";
	stack<string>* working_stack;
	queue<string>* postfix_expression_queue;
	expression_operator get_expression_operator(char exp_operator) const;
	double execute_operation(char exp_operator, double value_one, double value_two) const;

	///==================================================
	int nvalor = 1;
	queue<digit>* values_queue;
	double_linked_list<digit>* values_list;
	stack<digit>*  operators_stack;

	//============================
	bool int_try_parse(string val, int& num) const;
	static bool is_operator(string value);
	

public:
	expression_handler();
	expression_handler(string infix_expression);
	~expression_handler();
	void set_infix_expression(string infix_expression);
	string get_infix_expression() const;
	void create_postfix_expression();
	void print_postfix_expresion() const;
	double evaluate_expresion() const;

	void ver_lista_valores();
	void ver_cola_valores();
	string clean_expression(string);

	char get_expression_sign(char prev_exp_operator, char current_exp_operator);
	void clean_expression_2(string infix_expression);
	void ver_pila_operadores();
	void create_postfix();
	void calcula_exp_pos();
};