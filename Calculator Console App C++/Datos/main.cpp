
#include"control.h"


int main(){
	//control* ctr = new control();
	//
	//	control* C = new control();
	//	C->control_inicio();
	//	delete C;



	//CONSOLE_FONT_INFOEX cfi;
	//cfi.cbSize = sizeof(cfi);
	//cfi.nFont = 0;
	//cfi.dwFontSize.X = 0;                   // Width of each character in the font
	//cfi.dwFontSize.Y = 24;                  // Height
	//cfi.FontFamily = FF_DONTCARE;
	//cfi.FontWeight = FW_NORMAL;
	//SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);


	//ctr->calcula_pos();
	//ctr->proceso_ver_resultado();
	//ctr->proceso_exp_posfija();

	auto exp_handler = new expression_handler();
	exp_handler->clean_expression("(+-+----88+(--123)*-+------(10^+++--+++---2))^--++-345*-34");



	system("pause");
	return 0;
}




