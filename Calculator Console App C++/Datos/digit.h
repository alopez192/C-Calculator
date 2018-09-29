#pragma once
#include <string>
using namespace std;

class digit{
	bool is_numeric;
	bool is_part_negative_expression;
	string value;
public:
	digit(string, bool is_numeric);
	digit(string, bool is_numeric, bool is_negative_expression);
	digit();
	~digit();
	bool is_numeric_value() const;
	void set_is_numeric(bool);
	char get_exp_operator() const;
	double get_numeric_value() const;
	bool is_negative_expression() const;
	void set_value(string);
	string get_value() const;
	friend ostream & operator<<(ostream&,digit&); //salida
	friend bool operator== (const digit & digit1,const digit&digit2);
};