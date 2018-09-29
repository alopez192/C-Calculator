#include <iostream>
#include <windows.h>
#include "expression_handler.h"
int main(){

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	string expressions[] = { "(34--2)+(21/-7)", "-(42/6)-+-3*4","-15+3*-+(9*4)", "(---8)^2+(-3)^3","-5^2-(-5)^2", "-+-+-0-(-+-+-7)^2" };
	expression_handler* exp_handler;
	for (auto index =0; index < expressions->length(); index++)
	{
		cout << "Incoming expression: " << expressions[index] << endl;
		exp_handler = new expression_handler(expressions[index]);
		exp_handler->clean_expression(expressions[index]);
		cout << "Normalized incoming expression: " << endl;
		exp_handler->get_normalized_expression().print();
		exp_handler->create_postfix_expression();
		cout << "Postfix expression: " << endl;
		exp_handler->get_postfix_expression().print_forward();
		cout << "Resultado: " << exp_handler->evaluate_expresion() << endl;
		cout << "=================================================================================" << endl;
	}



	system("pause");
	return 0;
}




