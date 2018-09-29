#include "expression_handler.h"
#include "digit.h"

expression_handler::expression_handler(string infix_expression)
{
	this->infix_expression = infix_expression;
	this->normalized_infix_expression = new queue<digit>();
	this->working_stack = new stack<digit>();
	this->postfix_expression = new queue<digit>();
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

queue<digit>& expression_handler::get_postfix_expression() const
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
				postfix_expression->enqueue(exp_digit);
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
								postfix_expression->enqueue(working_stack->pop());
								top_operator = get_expression_operator(working_stack->peek().get_exp_operator());
							}
							working_stack->pop(); //remove '(' character after pull everything out
						}
						else
						{
							while (!working_stack->is_empty() && !(incoming_operator.get_priority_exp() > top_operator.get_priority_stack()))
							{
								postfix_expression->enqueue(working_stack->pop());
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
			postfix_expression->enqueue(working_stack->pop());
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
	double_linked_list<double> numbers;
	double_linked_list<char> operators;
	bool is_descending_eval = true;

	while (!this->postfix_expression->is_empty())
	{
		auto exp_digit = this->postfix_expression->dequeue();
		if (exp_digit.is_numeric_value())
		{
			numbers.add_back(exp_digit.get_numeric_value());
		}
		else
		{
			operators.add_back(exp_digit.get_exp_operator());
		}
	}

	//Validate special case
	auto back_operator = operators.get_back();
	auto is_special_case = false;

	if (operators.get_size() > 1 && back_operator != nullptr)
	{
		auto prev_back_operator = get_expression_operator(back_operator->get_prev()->get_data());
		if (back_operator->get_data() == '-' && prev_back_operator.get_priority_exp() == 4)
		{
			operators.delete_element(operators.get_size() - 1);
			is_special_case = true;
		}
		else if (back_operator->get_data() == '-' && prev_back_operator.get_expresion_operator() == '*')
		{
			is_special_case = true;
		}
	}

	auto const is_times_expression = operators.find_element('*') != nullptr && operators.find_element('^') == nullptr && operators.find_element('/') == nullptr;

	while (!operators.is_empty())
	{
		auto exp_operator = get_expression_operator((is_descending_eval ? operators.get_back() : operators.get_front())->get_data());
		auto exp_number = is_descending_eval ? numbers.get_back() : numbers.get_front();

		if (exp_operator.get_priority_exp() == 1 && ((operators.get_size() == 1 && numbers.get_size() != 2) || operators.get_size() >= 2))
		{
			exp_number->set_data(execute_operation('*', exp_number->get_data(), exp_operator.get_expresion_operator() == '-' ? -1 : 1));
			operators.delete_element(is_descending_eval ? operators.get_size() - 1 : 0);
			continue;
		}
		value_one = is_descending_eval ? exp_number->get_prev()->get_data() : exp_number->get_data();
		value_two = is_descending_eval ? exp_number->get_data() : exp_number->get_next()->get_data();

		if (numbers.get_size() == 2 && operators.get_size() == 1 && exp_operator.get_priority_exp() == 1 && value_two < 0)
		{
			result = execute_operation(exp_operator.get_expresion_operator(), value_two, value_one);
		}
		else
		{
			result = execute_operation(exp_operator.get_expresion_operator(), value_one, value_two);
		}
		numbers.delete_element(is_descending_eval ? numbers.get_size() - 1 : 0);
		numbers.delete_element(is_descending_eval ? numbers.get_size() - 1 : 0);
		if (is_descending_eval)
			numbers.add_back(result);
		else
			numbers.add_front(result);

		is_descending_eval ? operators.delete_element(operators.get_size() - 1) : operators.delete_element(0);
		is_descending_eval = !is_times_expression ? !is_descending_eval : true;
	}

	result = 0;
	while (!numbers.is_empty())
	{
		auto const exp_number_1 = is_descending_eval ? (numbers.get_back() != nullptr ? numbers.get_back() : numbers.get_front()) : (numbers.get_front() != nullptr ? numbers.get_front() : numbers.get_back());
		if (exp_number_1 != nullptr)
		{
			value_one = exp_number_1->get_data();

			if (numbers.get_size() % 2 == 0)
			{
				auto const exp_number_2 = is_descending_eval ? numbers.get_back()->get_prev() : numbers.get_front()->get_next();
				value_two = exp_number_2->get_data();
				result += value_one + value_two;
				numbers.delete_element(is_descending_eval ? numbers.get_size() - 1 : 0);
				numbers.delete_element(is_descending_eval ? numbers.get_size() - 1 : 0);
			}
			else
			{
				result += value_one;
				numbers.delete_element(is_descending_eval ? numbers.get_size() - 1 : 0);
			}
		}
	}
	return (is_special_case && !is_times_expression ? result * -1 : result);
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
					//continuous_less = false;
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
			auto back_digit = this->normalized_infix_expression->peek_back();
			if (prev_exp_operator == '-' && continuous_less || has_prev_higher_operator || ( !back_digit.is_numeric_value() && back_digit.get_exp_operator() == '(')) //convert number to minus in case of any prev less operator
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
	postfix_expression->print();
}