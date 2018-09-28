#include"digit.h"


digit::digit(const string value, const bool is_numeric){
	this->value = value;
	this->is_numeric = is_numeric;

}
digit::digit(const char exp_operator, const bool is_numeric){
	this->exp_operator = exp_operator;
	this->is_numeric = is_numeric;
}
digit::digit(){
	this->value = "";
	this->exp_operator = ' ';
	this->is_numeric = false;
}
bool digit::is_numeric_value() const
{
	return is_numeric;
}
void digit::set_is_numeric(const bool is_numeric_value){
	this->is_numeric = is_numeric_value;
}
void digit::set_exp_operator(const char exp_operator){
	this->exp_operator = exp_operator;
}
char digit::get_exp_operator() const
{
	return exp_operator;
}
void digit::set_value(const string value){
	this->value = value;
}
string digit::get_value() const
{
	return value;
}
ostream & operator<<(ostream& outp, digit&T){
	outp<< T.value;
	return outp;
}
digit::~digit()
{
}
