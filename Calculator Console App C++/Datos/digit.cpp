#include"digit.h"

digit::digit(string value, bool is_numeric)
{
	this->value = value;
	this->is_numeric = is_numeric;
	this->is_part_negative_expression = false;
}
digit::digit(string value, bool is_numeric, bool is_negative_expression) {
	this->value = value;
	this->is_numeric = is_numeric;
	this->is_part_negative_expression = is_negative_expression;
}
digit::digit(){
	this->value = "";
	this->is_numeric = false;
}
bool digit::is_numeric_value() const
{
	return is_numeric;
}
void digit::set_is_numeric(const bool is_numeric_value){
	this->is_numeric = is_numeric_value;
}
char digit::get_exp_operator() const
{
	return this->value[0];
}
double digit::get_numeric_value() const
{
	if (this->is_numeric)
		return stod(this->value);
	return 0.0;
}
bool digit::is_negative_expression() const
{
	return this->is_part_negative_expression;
}
void digit::set_value(const string value){
	this->value = value;
}
string digit::get_value() const
{
	return value;
}
ostream & operator<<(ostream& outp, digit&T){
	outp << T.value;
	return outp;
}
bool operator==(const digit & digit1,const digit & digit2)
{
	return digit1.get_value() == digit2.get_value();
}
digit::~digit()
{
}
