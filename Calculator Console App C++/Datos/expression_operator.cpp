#include "expression_operator.h"

expression_operator::expression_operator()
{
	this->exp_operator = ' ';
	this->priority_exp = -1;
	this->priority_stack = -1;
}

expression_operator::expression_operator(char op, int priority_exp, int priority_stack)
{
	this->exp_operator = op;
	this->priority_exp = priority_exp;
	this->priority_stack = priority_stack;
}

expression_operator::~expression_operator() = default;

void expression_operator::set_expresion_operator(char expresion_operator)
{
	this->exp_operator = expresion_operator;
}

void expression_operator::set_priority_exp(int priority_exp)
{
	this->priority_exp = priority_exp;
}

void expression_operator::set_priority_stack(int priority_stack)
{
	this->priority_stack = priority_stack;
}

char expression_operator::get_expresion_operator() const
{
	return this->exp_operator;
}

int expression_operator::get_priority_exp() const
{
	return this->priority_exp;
}

int expression_operator::get_priority_stack() const
{
	return this->priority_stack;
}
