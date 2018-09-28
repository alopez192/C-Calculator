#pragma once
#include <iostream>
#include "expression_operator.h"
using namespace std;

class expression_evaluator
{
	double operator_1;
	double operator_2;
	expression_operator* exp_operator;

public:
	expression_evaluator();
	expression_evaluator(double operator_1, double operator_2, expression_operator* exp_operator);
	~expression_evaluator();
	void set_operator_1(double operator_1);
	void set_operator_2(double operator_2);
	void set_expression_operator(expression_operator* exp_operator);
	double get_operator_1() const;
	double get_operator_2() const;
	expression_operator* get_expression_operator() const;
	double get_expression_result() const;
};