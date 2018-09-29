#include "expression_handler.h"
#include "digit.h"

expression_handler::expression_handler(string infix_expression)
{
	this->infix_expression = infix_expression;
	this->normalized_infix_expression = new queue<digit>();
	this->working_stack = new stack<digit>();
	this->postfix_expression = new double_linked_list<digit>();
}

expression_handler::~expression_handler() = default;

void expression_handler::set_infix_expression(string infix_expression)
{
	this->infix_expression = infix_expression;
}

string expression_handler::get_infix_expression() const
{
	return this->infix_expression;
}

expression_operator expression_handler::get_expression_operator(char exp_operator) const
{
	switch (exp_operator)
	{
	case '^':
		return expression_operator(exp_operator, 4, 3);
	case '*':
		return expression_operator(exp_operator, 2, 2);
	case '/':
		return expression_operator(exp_operator, 2, 2);
	case '+':
		return expression_operator(exp_operator, 1, 1);
	case '-':
		return expression_operator(exp_operator, 1, 1);
	case '(':
		return expression_operator(exp_operator, 5, 0);
	case ')':
		return expression_operator(exp_operator, -1, -1);
	default:
		return expression_operator();
	}
}

char expression_handler::get_expression_sign(char prev_exp_operator, char current_exp_operator) const
{
	auto result_operator = ' ';
	if (prev_exp_operator == '-' && current_exp_operator == '-')
	{
		result_operator = '+';
	}
	else if (prev_exp_operator == '+' && current_exp_operator == '-')
	{
		result_operator = '-';
	}
	else if (prev_exp_operator == '+' && current_exp_operator == '+')
	{
		result_operator = '+';
	}
	else
	{
		result_operator = '-';
	}
	return result_operator;
}

double_linked_list<digit>& expression_handler::get_postfix_expression() const
{
	return *this->postfix_expression;
}

queue<digit>& expression_handler::get_normalized_expression() const
{
	return *this->normalized_infix_expression;
}

bool expression_handler::int_try_parse(string val, int &num) const
{
	bool result = false;
	if (val.length() == 1)
	{
		if (isdigit(val[0]))
		{
			num = stoi(val);
			result = true;
		}
		else
		{
			num = 0;
		}
	}
	else
	{
		num = stoi(val);
		result = true;
	}
	return result;
}

bool expression_handler::is_operator(string value)
{
	return value.length() == 1 && !isdigit(value[0]);
}

double expression_handler::execute_operation(char exp_operator, double value_one, double value_two) const
{
	double result = 0.0;
	switch (exp_operator)
	{
	case '^':
		result = value_two < 0 ? (pow(value_one, (value_two * -1)) * -1) : pow(value_one, value_two);
		break;
	case '*':
		result = value_one * value_two;
		break;
	case '/':
		result = value_one / value_two;
		break;
	case '+':
		result = value_one + value_two;
		break;
	case '-':
		result = value_one - value_two;
		break;
	default:
		result = 0.0;
		break;
	}
	return result;
}

void expression_handler::create_postfix_expression() const
{
	if (!this->normalized_infix_expression->is_empty())
	{
		while(!this->normalized_infix_expression->is_empty())
		{
			auto exp_digit = this->normalized_infix_expression->dequeue();
			if (exp_digit.is_numeric_value()) //if it is a digit, then we need to add it to the queue, but first check if the digit is greater than 9
			{
				postfix_expression->add_back(exp_digit);
			}
			else //do all logic for operators
			{
				if (working_stack->is_empty()) //if stack empty, just add the incoming operator
				{
					working_stack->push(exp_digit);
				}
				else
				{
					auto incoming_operator = get_expression_operator(exp_digit.get_exp_operator());
					auto top_operator = get_expression_operator(working_stack->peek().get_exp_operator());

					if (incoming_operator.get_priority_exp() > top_operator.get_priority_stack())
					{
						working_stack->push(exp_digit);
					}
					else
					{
						if (top_operator.get_expresion_operator() == '(' && incoming_operator.get_expresion_operator() != ')') //if the top is '(' then apply the incoming operator
						{
							working_stack->push(exp_digit);
						}

						if (exp_digit.get_exp_operator() == ')') //pull out all the operators until next opening parenthesis
						{
							while (!working_stack->is_empty() && top_operator.get_expresion_operator() != '(')
							{
								postfix_expression->add_back(working_stack->pop());
								top_operator = get_expression_operator(working_stack->peek().get_exp_operator());
							}
							working_stack->pop(); //remove '(' character after pull everything out
						}
						else
						{
							while (!working_stack->is_empty() && !(incoming_operator.get_priority_exp() > top_operator.get_priority_stack()))
							{
								postfix_expression->add_back(working_stack->pop());
								if (!working_stack->is_empty())
									top_operator = get_expression_operator(working_stack->peek().get_exp_operator());
								else
									break;
							}
							working_stack->push(exp_digit); //insert the incoming operator after all the lower precedence operators were pulled out
						}
					}
				}
			}
		}

		//pull all other operators that are left on the stack as the expression has reached the end of the evaluation
		while (!working_stack->is_empty())
		{
			postfix_expression->add_back(working_stack->pop());
		}
	}
	else
	{
		cout << "*** Invalid Expression ***" << endl;
	}
}

double expression_handler::evaluate_expresion()
{
	auto result = 0.0;
	auto value_one = 0.0;
	auto value_two = 0.0;
	auto is_complete_to_evaluate = false;
	int index = 0;
	auto numbers_count = 0;
	auto exp_digit = postfix_expression->get_front();
	auto is_less_expression = false;
	while(!this->postfix_expression->is_empty() && this->postfix_expression->get_size()>2)
	{
		if(exp_digit->get_data().is_numeric_value())
		{
			numbers_count++;
			if(value_one==0)
			{
				value_one = exp_digit->get_data().get_numeric_value();
			}
			else
			{
				if (numbers_count > 2)
				{
					value_one = value_two;
					value_two = exp_digit->get_data().get_numeric_value();
					is_complete_to_evaluate = true;
				}
				else {
					value_two = exp_digit->get_data().get_numeric_value();
					is_complete_to_evaluate = true;
				}
			}
		}
		else //case when it is an operator
		{
			if(is_complete_to_evaluate)
			{
				is_less_expression = exp_digit->get_prev()->get_prev()->get_data().is_negative_expression() 
										&& exp_digit->get_prev()->get_data().is_negative_expression() 
										&& exp_digit->get_data().is_negative_expression()
										&& exp_digit->get_next()!=nullptr
										&& exp_digit->get_next()->get_data().is_negative_expression();
				if(is_less_expression)
				{
					result = execute_operation(exp_digit->get_data().get_exp_operator(), value_one, value_two) * -1;
					auto new_index = index + 1;
					postfix_expression->add_after(digit(to_string(result), true), new_index);
					postfix_expression->delete_element(new_index--);
					postfix_expression->delete_element(new_index--);
					postfix_expression->delete_element(new_index--);
					postfix_expression->delete_element(new_index--);
				}
				else
				{
					result = execute_operation(exp_digit->get_data().get_exp_operator(), value_one, value_two);
					postfix_expression->add_after(digit(to_string(result), true), index);
					postfix_expression->delete_element(index--);
					postfix_expression->delete_element(index--);
					postfix_expression->delete_element(index--);
				}
				is_complete_to_evaluate = false;
				exp_digit = this->postfix_expression->get_front();
				index = 0;
				value_one = 0.0;
				value_two = 0.0;
				numbers_count = 0;
				continue;
			}
			value_one = 0.0;
			value_two = 0.0;
			numbers_count = 0;
		}
		index++; 
		
		exp_digit = exp_digit->get_next();
	}
	if (this->postfix_expression->get_size() == 1)
		result = this->postfix_expression->get_front()->get_data().get_numeric_value();
	else
		result = execute_operation('+', this->postfix_expression->get_front()->get_data().get_numeric_value(), this->postfix_expression->get_front()->get_next()->get_data().get_numeric_value());
	delete this->postfix_expression;
	this->postfix_expression = new double_linked_list<digit>();
	return result;
}

void expression_handler::clean_expression(string infix_expression)
{
	this->normalized_infix_expression = new queue<digit>();//clean prev data
	auto prev_exp_operator = ' ';
	auto is_negative_expression = false;
	auto continuous_less = false;
	auto has_prev_higher_operator = false;
	for (auto index = 0; index < (static_cast<int>(infix_expression.length())); index++)
	{
		const auto character = infix_expression[index];
		if (!isdigit(character))
		{
			if ((character == '-' || character == '+'))
			{
				if (index == 0)
				{
					continuous_less = true;
				}

				if(index > 0 && !has_prev_higher_operator && (infix_expression[index-1] == '/' || infix_expression[index - 1] == '*'))
				{
					has_prev_higher_operator = true;
				}
				
				if (prev_exp_operator != ' ')
					prev_exp_operator = get_expression_sign(prev_exp_operator, character); //evaluate incoming operator against prev operator. Applies only for '-' or '+'
				else
				{
					prev_exp_operator = character;
				}
			}
			else
			{
				if(index > 0 && (infix_expression[index-1] == '/' || infix_expression[index - 1] == '*' && character != '('  && ( character == '-' || prev_exp_operator == '-')))
				{
					prev_exp_operator = prev_exp_operator == ' ' ? character : prev_exp_operator;
					continuous_less = true;
					continue;
				}

				if ((prev_exp_operator == '-' && character == '(') || (character == ')' && is_negative_expression))
				{
					if(prev_exp_operator != ' ')
						this->normalized_infix_expression->enqueue(digit(string(1, prev_exp_operator), false, true));
					this->normalized_infix_expression->enqueue(digit(string(1, character), false, true));
					is_negative_expression = character != ')';
					prev_exp_operator = ' ';
					continue;
				}

				if (prev_exp_operator != ' ' && character == '(')//if ((prev_exp_operator == '-' || prev_exp_operator == '+')  && character == '(')
				{
					this->normalized_infix_expression->enqueue(digit(string(1, prev_exp_operator),false, is_negative_expression));
					prev_exp_operator = ' ';
				}

				this->normalized_infix_expression->enqueue(digit(string(1, character), false,is_negative_expression));
			}
		}
		else
		{
			string value;
			value += character;

			if (isdigit(infix_expression[index + 1])) //check if number is greater than 9
			{
				auto sub_index = index + 1;
				auto sub_number_character = infix_expression[sub_index];
				while (isdigit(sub_number_character))
				{
					value += sub_number_character;
					sub_number_character = infix_expression[++sub_index];
				}
				index = sub_index - 1;
			}
			if (prev_exp_operator == '-' && continuous_less || has_prev_higher_operator) //convert number to minus in case of any prev less operator
			{
				value.insert(0, 1, prev_exp_operator);
				this->normalized_infix_expression->enqueue(digit(value, true, is_negative_expression));
				prev_exp_operator = ' ';
				has_prev_higher_operator = false;
				continuous_less = false;
			}
			else if (prev_exp_operator == '-' && is_negative_expression) //convert number to minus in case of any prev less operator
			{
				this->normalized_infix_expression->enqueue(digit(value, true, true));
				prev_exp_operator = ' ';
			}
			else
			{
				if (prev_exp_operator != ' ') {
					this->normalized_infix_expression->enqueue(digit(string(1, prev_exp_operator),false, is_negative_expression));
					prev_exp_operator = ' ';
				}
				this->normalized_infix_expression->enqueue(digit(value, true, is_negative_expression));
			}
		}
	}
}

void expression_handler::print_postfix_expresion() const
{
	postfix_expression->print_forward();
}