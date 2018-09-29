#pragma once
#include <string>
using namespace std;

class digit{
	bool is_numeric;
	string value;
public:
	digit(string, bool);
	digit();
	~digit();
	bool is_numeric_value() const;
	void set_is_numeric(bool);
	char get_exp_operator() const;
	double get_numeric_value() const;
	void set_value(string);
	string get_value() const;
	friend ostream & operator<<(ostream&,digit&); //salida
};