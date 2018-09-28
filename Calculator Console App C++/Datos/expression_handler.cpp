#include "expression_handler.h"


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

	default: return expression_operator();
	}
}
//=====================================================================================


void expression_handler::create_postfix()
{
	digit e = digit();
	char character;
	
	while (!values_queue->is_empty()){
		    e = values_queue->dequeue();

			if (e.is_numeric_value())
			{
				values_list->add(e);
			}
			else 
			{
				character = *e.get_value().c_str();

				if (operators_stack->is_empty())
				{
				
					operators_stack->push(e);
				}
				else
				{
					auto incoming_operator = get_expression_operator(character);
					char y = *operators_stack->peek().get_value().c_str();
					auto top_operator = get_expression_operator(y);


					if (incoming_operator.get_priority_exp() > top_operator.get_priority_stack())
					{
						
						operators_stack->push(e);
					}
					else
					{
						if (top_operator.get_expresion_operator() == '(')
						{
							
							operators_stack->push(e);
						}

						if (character == ')') 
						{
							char x;
							while (!operators_stack->is_empty() && top_operator.get_expresion_operator() != '(')
							{
								values_list->add(operators_stack->peek());
								x = *operators_stack->peek().get_value().c_str();
								top_operator = get_expression_operator(x);
							}
							
							operators_stack->pop();
						}
						else
						{
							while (!operators_stack->is_empty()  && !(incoming_operator.get_priority_exp() > top_operator.get_priority_stack()))
							{
								values_list->add(operators_stack->peek());
								if (!operators_stack->is_empty()){
									char x = *operators_stack->peek().get_value().c_str();
									top_operator = get_expression_operator(x);
								}
								else
									break;
							}
						
							operators_stack->push(e);
						}
					}
				}
			}
		}

	while (!operators_stack->is_empty())
	{
		values_list->add(operators_stack->peek());
	}
}


//=====================================================================================
void expression_handler::calcula_exp_pos(){
	digit new_digit = digit();
	int nuevo_operador = 0;
	int val_en_pila = 0;
	char y;

	while (!values_queue->is_empty()){

		new_digit = values_queue->dequeue();

		if (new_digit.is_numeric_value())
		{
			values_list->add(new_digit);
		}
		else{
			y = *new_digit.get_value().c_str();

			if (operators_stack->is_empty()){

				operators_stack->push(new_digit);
			}
			char x = *operators_stack->peek().get_value().c_str();

			nuevo_operador = get_expression_operator(y).get_priority_exp();
			val_en_pila = get_expression_operator(x).get_priority_stack();

			if (nuevo_operador > val_en_pila || y == ')' || y == '(')
			{
				operators_stack->push(new_digit);
			}
			else{

				if (nuevo_operador < val_en_pila)
				{
					char x;
					while (nuevo_operador < val_en_pila){

						x = *operators_stack->peek().get_value().c_str();
						if (x!='(' && x!=')'){
							values_list->add(operators_stack->peek());
						}
						operators_stack->pop();
						x = *operators_stack->peek().get_value().c_str();
						val_en_pila = get_expression_operator(x).get_priority_stack();

					}
					operators_stack->push(new_digit);
				}

				if (nuevo_operador == val_en_pila)
				{
					char x;
					while (nuevo_operador > val_en_pila){

						x = *operators_stack->peek().get_value().c_str();
						if (x != '('&&x!=')'){ 
							values_list->add(operators_stack->peek()); 
						}

						operators_stack->pop();
						x = *operators_stack->peek().get_value().c_str();
						val_en_pila = get_expression_operator(x).get_priority_stack();
					}
					operators_stack->push(new_digit);
				}
			}
		}
		}//while

		if (!operators_stack->is_empty()){
			char x;

			while (!operators_stack->is_empty()){
				x = *operators_stack->peek().get_value().c_str();
				if (x!='(' && x!=')'){
					values_list->add(operators_stack->peek());
				}
			   operators_stack->pop();
			}
		}

	}



string expression_handler::clean_expression(string expression){
	auto temp = new queue<digit>();
	string s = "";
	auto predecesor = false;

	if (!expression.empty()){
		for (auto i = 0; i < expression.length() ; i++) {
			auto c = expression[i];
			if (isdigit(c)){
				if (isdigit(expression[i + 1])){

					s = string(1,c);
					int pos = i + 1;
					
					while (isdigit(expression[pos]))
					{
						s += string(1,expression[pos]);
						pos++;
						i++;
					}
					
					int num = stoi(s);
					values_queue->enqueue(digit(to_string(num), true));
					temp->enqueue(digit(to_string(num), true));
				}
				else{

					values_queue->enqueue(digit(string(1, c), true));
					temp->enqueue(digit(string(1, c), true));
				}

				predecesor = true;
			}
			else{

				switch (expression[i])
				{
				case '-':
					nvalor = nvalor*-1;
					if (expression[i + 1] == '('&& !predecesor){
						if (nvalor == -1){
							values_queue->enqueue(digit(string(1, '-'), false));
							temp->enqueue(digit(string(1, '-'), false));
							nvalor = 1;
						}
						
					}if (expression[i + 1] == '('&& predecesor){
						if (nvalor == -1){
							values_queue->enqueue(digit(string(1, '-'), false));
							temp->enqueue(digit(string(1, '-'), false));
							nvalor = 1;
						}
						if (nvalor == 1){
							values_queue->enqueue(digit(string(1, '+'), false));
							temp->enqueue(digit(string(1, '+'), false));
							nvalor = 1;
						}

					}
					//===========================================================
					if (isdigit(expression[i + 1]) && !predecesor){
						string v = "";
						int pos = i + 1;
						
						if (isdigit(expression[pos])){
							
							
							while (isdigit(expression[pos]))
							{
								v += string(1,expression[pos]);
								pos++;
								i++;
							}
							int num = stoi(v);
							num = num*nvalor;

							values_queue->enqueue(digit(to_string(num), true));
							temp->enqueue(digit(to_string(num), true));
							
						}
						predecesor = true;
						nvalor = 1;
					}
					else{
						if (isdigit(expression[i + 1]) && predecesor){
							if (nvalor == -1){

								values_queue->enqueue(digit(string(1, '-'), false));
								temp->enqueue(digit(string(1, '-'), false));

							}
							else{
								values_queue->enqueue(digit(string(1, '+'), false));
								temp->enqueue(digit(string(1, '+'), false));

							}
							nvalor = 1;
							predecesor = true;
						}
					}
					//==============================================================
					break;
				case '+':
					nvalor = nvalor * 1;
					if (expression[i + 1] == '(' && predecesor ){
						if (nvalor == -1){

							values_queue->enqueue(digit(string(1,'-'), false));
							temp->enqueue(digit(string(1, '-'), false));

						}
						else{
							
							values_queue->enqueue(digit(string(1, '+'), false));
							temp->enqueue(digit(string(1, '+'), false));

						}
						nvalor = 1;
					}
					else{
						if (expression[i + 1] == '(' && !predecesor){
							if (nvalor == -1){

								values_queue->enqueue(digit(string(1, '-'), false));
								temp->enqueue(digit(string(1, '-'), false));
							}
							nvalor = 1;
						}
					}if (isdigit(expression[i + 1]) && !predecesor){
							string v = "";
							int pos = i + 1;
							while (isdigit(expression[pos]))
							{
								v += string(1, expression[pos]);
								pos++;
								i++;
							}
							int num = stoi(v);
							num = num*nvalor;

							values_queue->enqueue(digit(to_string(num), true));
							temp->enqueue(digit(to_string(num), true));

							nvalor = 1;
							predecesor = true;
						}else{
						if (isdigit(expression[i + 1]) && predecesor == true){
							if (nvalor == -1){

								values_queue->enqueue(digit(string(1, '-'), false));
								temp->enqueue(digit(string(1, '-'), false));

							}
							else{
								values_queue->enqueue(digit(string(1, '+'), false));
								temp->enqueue(digit(string(1, '+'), false));
							}
							nvalor = 1;
							predecesor = true;
						}
					}
					break;
				case '(':

					values_queue->enqueue(digit(string(1, c), false));
					temp->enqueue(digit(string(1, c), false));
					predecesor = false;
					break;
				case ')':

					values_queue->enqueue(digit(string(1, c), false));
					temp->enqueue(digit(string(1, c), false));
					
					break;
				case '*':

					values_queue->enqueue(digit(string(1, c), false));
					

					break;
				case '^':

					 values_queue->enqueue(digit(string(1, c), false));
					 temp->enqueue(digit(string(1, c), false));

				default:
					break;
				}
			}
		}//for
	}
	else
	{
		
		cout << "*** Invalid Expression ***" << endl;
	}

	while (!temp->is_empty()){
	exp_pos += temp->dequeue().get_value();
	}
	return exp_pos;
}

void expression_handler::ver_lista_valores(){
	this->values_list->print_forward();

}
void expression_handler::ver_cola_valores(){
	this->values_queue->print();

}
void expression_handler::ver_pila_operadores(){
	this->operators_stack->print();

}


bool expression_handler::int_try_parse(string val, int & num) const
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
		result = value_two < 0 ? (pow(value_one, (value_two*-1)) *-1) : pow(value_one, value_two);
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

expression_handler::expression_handler()
{
	this->infix_expression = "";
	this->working_stack = new stack<string>();
	this->postfix_expression_queue = new queue<string>();

    //===========================================================
	this->values_queue = new queue<digit>();
	this->operators_stack = new stack<digit>();
	this->values_list = new  double_linked_list<digit>();
}

expression_handler::expression_handler(string infix_expression)
{
	this->infix_expression = infix_expression;
	this->working_stack = new stack<string>();
	this->postfix_expression_queue = new queue<string>();

	//===========================================================
	this->values_queue = new queue<digit>();
	this->operators_stack= new stack<digit>();
	this->values_list = new  double_linked_list<digit>();
}


void expression_handler::create_postfix_expression()
{
	if (!this->infix_expression.empty())
	{
		for (auto exp_index = 0; exp_index < static_cast<int>(infix_expression.length()); exp_index++) {
			auto character = infix_expression[exp_index];
			if (isdigit(character)) //if it is a digit, then we need to add it to the queue, but first check if the digit is greater than 9
			{
				auto digit = string(1, character);
				auto inner_exp_index = exp_index + 1;
				auto is_operator = false;
				while (inner_exp_index != (infix_expression.length()) && !is_operator)
				{
					character = infix_expression[inner_exp_index];
					if (isdigit(character))
					{
						digit.append(1, character);
						inner_exp_index++;
					}
					else
					{
						is_operator = true;
					}
				}
				exp_index = inner_exp_index == exp_index + 1 ? exp_index : inner_exp_index - 1;
				postfix_expression_queue->enqueue(digit);
			}
			else //do all logic for operators
			{
				if (working_stack->is_empty())//if stack empty, just add the incoming operator
				{
					working_stack->push(string(1, character));
				}
				else
				{
					auto incoming_operator = get_expression_operator(character);
					auto top_operator = get_expression_operator(working_stack->peek()[0]);

					if (incoming_operator.get_priority_exp() > top_operator.get_priority_stack())
					{
						working_stack->push(string(1, character));
					}
					else
					{
						if (top_operator.get_expresion_operator() == '('&&incoming_operator.get_expresion_operator()!=')') //if the top is '(' then apply the incoming operator
						{
							working_stack->push(string(1, character));
						}

						if (character == ')') //pull out all the operators until next opening parenthesis
						{
							while (!working_stack->is_empty() && top_operator.get_expresion_operator() != '(')
							{
								postfix_expression_queue->enqueue(working_stack->pop());
								top_operator = get_expression_operator(working_stack->peek()[0]);
							}
							working_stack->pop(); //remove '(' character after pull everything out
						}
						else
						{
							while (!working_stack->is_empty() && !(incoming_operator.get_priority_exp() > top_operator.get_priority_stack()))
							{
								postfix_expression_queue->enqueue(working_stack->pop());
								if (!working_stack->is_empty())
									top_operator = get_expression_operator(working_stack->peek()[0]);
								else
									break;
							}
							working_stack->push(string(1, character));//insert the incoming operator after all the lower precedence operators were pulled out
						}
					}
				}
			}
		}

		//pull all other operators that are left on the stack as the expression has reached the end of the evaluation
		while (!working_stack->is_empty())
		{
			postfix_expression_queue->enqueue(working_stack->pop());
		}
	}
	else
	{
		cout << "*** Invalid Expression ***" << endl;
	}
}


void expression_handler::print_postfix_expresion() const
{
	postfix_expression_queue->print();
}

double expression_handler::evaluate_expresion() const
{
	auto result = 0.0;
	auto value_one = 0.0;
	auto value_two = 0.0;
	double_linked_list<double> numbers;
	double_linked_list<char> operators;
	bool is_descending_eval = true;

	while (!this->postfix_expression_queue->is_empty())
	{
		string value = this->postfix_expression_queue->dequeue();
		if (!is_operator(value)) {
			numbers.add_back(stod(value));
		}
		else {
			operators.add_back(value[0]);
		}
	}


	//Validate special case
	auto back_operator = operators.get_back();
	auto is_special_case = false;
	
	if (operators.get_size()>1 && back_operator != nullptr)
	{
		auto prev_back_operator = get_expression_operator(back_operator->get_prev()->get_data());
		if (back_operator->get_data() == '-' &&  prev_back_operator.get_priority_exp() == 4)
		{
			operators.delete_element(operators.get_size() - 1);
		}
		else if(back_operator->get_data() == '-' &&  prev_back_operator.get_expresion_operator() == '*')
		{
			is_special_case = true;
		}
	}

	auto const is_times_expression = operators.find_element('*') != nullptr && operators.find_element('^') == nullptr && operators.find_element('/') == nullptr;

	while (!operators.is_empty()) {
		auto exp_operator = get_expression_operator((is_descending_eval ? operators.get_back() : operators.get_front())->get_data());
		auto exp_number = is_descending_eval ? numbers.get_back() : numbers.get_front();

		if (exp_operator.get_priority_exp() == 1 && (( operators.get_size() == 1 && numbers.get_size() != 2) || operators.get_size() >= 2)) {
			exp_number->set_data(execute_operation('*', exp_number->get_data(), exp_operator.get_expresion_operator() == '-' ? -1 : 1));
			operators.delete_element(is_descending_eval ? operators.get_size() - 1 : 0);
			continue;
		}
		value_one = is_descending_eval ? exp_number->get_prev()->get_data() : exp_number->get_data();
		value_two = is_descending_eval ? exp_number->get_data() : exp_number->get_next()->get_data();

		
		if (numbers.get_size() == 2 && operators.get_size() == 1 && exp_operator.get_priority_exp() == 1 && value_two < 0) {
			result = execute_operation(exp_operator.get_expresion_operator(), value_two, value_one);
		}
		else {
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
	while (!numbers.is_empty()) {
		auto const exp_number_1 = is_descending_eval ? (numbers.get_back() != nullptr ? numbers.get_back() : numbers.get_front()) : (numbers.get_front() != nullptr ? numbers.get_front() : numbers.get_back());
		if(exp_number_1 != nullptr)
		{
			value_one = exp_number_1->get_data();
			
			if (numbers.get_size() % 2 == 0) {
				auto const exp_number_2 = is_descending_eval ? numbers.get_back()->get_prev() : numbers.get_front()->get_next();
				value_two = exp_number_2->get_data();
				result += value_one + value_two;
				numbers.delete_element(is_descending_eval ? numbers.get_size() - 1 : 0);
				numbers.delete_element(is_descending_eval ? numbers.get_size() - 1 : 0);
			}
			else {
				result += value_one;
				numbers.delete_element(is_descending_eval ? numbers.get_size() - 1 : 0);
			}
		}
	}
	return (is_special_case && !is_times_expression ? result * -1 : result);
}

void expression_handler::set_infix_expression(string infix_expression)
{
	this->infix_expression = infix_expression;
}

string expression_handler::get_infix_expression() const
{
	return this->infix_expression;
}

expression_handler::~expression_handler()
= default;

char expression_handler::get_expression_sign(char prev_exp_operator, char current_exp_operator)
{
	auto result_operator = ' ';
	if(prev_exp_operator == '-' && current_exp_operator == '-')
	{
		result_operator = '+';
	}
	else if(prev_exp_operator == '+' && current_exp_operator == '-')
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

void expression_handler::clean_expression_2(string infix_expression)
{
	auto normalized_expression_queue = new queue<digit>();
	auto prev_exp_operator = ' ';
	for (auto index = 0; index < (static_cast<int>(infix_expression.length())); index++)
	{
		const auto character = infix_expression[index];

		if (!isdigit(character)) {
			if ((character == '-' || character == '+'))
			{
				if(prev_exp_operator != ' ')
					prev_exp_operator = get_expression_sign(prev_exp_operator, character);
				else
				{
					prev_exp_operator = character;
				}
			}
			else
			{
				if(prev_exp_operator != ' ')
				{
					normalized_expression_queue->enqueue(digit(string(1, prev_exp_operator), false));
					prev_exp_operator = ' ';
				}
				normalized_expression_queue->enqueue(digit(string(1, character), false));
			}
		}
		else
		{
			string value;
			value += character;

			if(isdigit(infix_expression[index + 1]))
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

			if(prev_exp_operator != ' ' && prev_exp_operator == '-')
			{
				value.insert(0,1,prev_exp_operator);
				normalized_expression_queue->enqueue(digit(value, true));
				prev_exp_operator = ' ';
			}else
			{
				prev_exp_operator = ' ';
				normalized_expression_queue->enqueue(digit(value, true));
			}
		}
	}
	normalized_expression_queue->print();
}
