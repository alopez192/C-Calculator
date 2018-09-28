#include "expression_evaluator.h"

expression_evaluator::expression_evaluator()
{
	this->operator_1 = 0;
	this->operator_2 = 0;
	this->exp_operator = new expression_operator();
}

expression_evaluator::expression_evaluator(const double operator_1, const double operator_2, expression_operator* exp_operator)
{
	this->operator_1 = operator_1;
	this->operator_2 = operator_2;
	this->exp_operator = exp_operator;
}

expression_evaluator::~expression_evaluator() = default;

void expression_evaluator::set_operator_1(double operator_1)
{
	this->operator_1 = operator_1;
}

void expression_evaluator::set_operator_2(double operator_2)
{
	this->operator_2 = operator_2;
}

void expression_evaluator::set_expression_operator(expression_operator* exp_operator)
{
	this->exp_operator = exp_operator;
}

double expression_evaluator::get_operator_1() const
{
	return this->operator_1;
}

double expression_evaluator::get_operator_2() const
{
	return this->operator_2;
}

expression_operator* expression_evaluator::get_expression_operator() const
{
	return this->exp_operator;
}

double expression_evaluator::get_expression_result() const
{
	double result = 0.0;
	switch (this->exp_operator->get_expresion_operator())
	{
	case '^':
		result = pow(operator_1, operator_2);
		break;
	case '*':
		result = operator_1 * operator_2;
		break;
	case '/':
		result = operator_1 / operator_2;
		break;
	case '+':
		result = operator_1 + operator_2;
		break;
	case '-':
		result = operator_1 - operator_2;
		break;
	default:
		throw new exception("Invalid Math Operation");
	}
	return result;
}
