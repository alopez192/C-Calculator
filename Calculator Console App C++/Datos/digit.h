#pragma once
#include <string>

using namespace std;

class digit{
private:
	bool is_numeric;
	char exp_operator{};
	string value;

public:

	digit(string, bool);
	digit(char, bool);
	digit();
	~digit();
	bool is_numeric_value() const;
	void set_is_numeric(bool);
	void set_exp_operator(char);
	char get_exp_operator() const;
	void set_value(string);
	string get_value() const;
	friend ostream & operator<<(ostream&,digit&); //salida
};