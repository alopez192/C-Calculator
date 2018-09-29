#include <iostream>
#include <windows.h>
#include "expression_handler.h"
int main(){

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 34;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	string expressions[] = {"-6*-3+(--2)^2", "+-+--(---6*4)+(-5)^2","34-234", "28/7","31*23", "-3+-5","7*-3", "-8/-4","(34--2)+(21/-7)", "-(42/6)-+-3*4","-15+3*-+(9*4)", "(---8)^2+(-3)^3","-5^2-(-5)^2", "-+-+-0-(-+-+-7)^2" };
	expression_handler* exp_handler;
	for (const auto& expression : expressions)
	{
		cout << "Incoming expression: " << expression << endl;
		exp_handler = new expression_handler(expression);
		exp_handler->clean_expression(expression);
		cout << "Normalized incoming expression: " << endl;
		exp_handler->get_normalized_expression().print();
		exp_handler->create_postfix_expression();
		cout << "Postfix expression: " << endl;
		exp_handler->get_postfix_expression().print();
		cout << "Resultado: " << exp_handler->evaluate_expresion() << endl;
		cout << "=================================================================================" << endl;
	}



	system("pause");
	return 0;
}




