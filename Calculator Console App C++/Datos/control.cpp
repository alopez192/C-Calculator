#include"control.h"
#include "interfaz.h"

control::control() {
	
	expression_handl = new expression_handler(""); 

}
control::~control() {
	delete expression_handl;
}
void control::proceso_inicio() {
	interfaz::ventana_inicio();
	//Sleep(1000);
	system("cls");
	//Sleep(1000);
}

void control::control_inicio() {
	{
		int op = 0;
		proceso_inicio(); 
		do {
			system("cls");
			op = interfaz::ventana_menu();
			switch (op){
			case 1: hacer_calculos();        break;
			case 2: proceso_exp_posfija();     break;
			case 3: proceso_ver_resultado();      break;
			case 4: proceso_final();       break;
			}  

		} while (op != 4);

	}
	//Sleep(4000);
}
void control::hacer_calculos(){
	
	interfaz::ventana_calculadora("");

	cout << "\n\t\tDigite la expresion :";
	string ex ;
	cin >> ex;
	system("cls");
	interfaz::ventana_calculadora(ex);
	
	this->expression_handl->set_infix_expression(ex);

	calcula_pos();
	proceso_ver_resultado();
	proceso_exp_posfija();

	//Sleep(5000);
	system("cls");
}
void control::proceso_exp_posfija(){
	interfaz::ventana_exp_posfija();
	this->expression_handl->print_postfix_expresion();
	//Sleep(2500);
	system("cls");
}

void control::calcula_pos(){
	

}
void control::calcula_result(){
	
	cout << this->expression_handl->evaluate_expresion() << endl;
}
void control::proceso_ver_resultado(){
	interfaz::ven_ver_resultado();
	this->expression_handl->print_postfix_expresion();
	//Sleep(2500);
	system("cls");
}
void control::proceso_final(){
	interfaz::ventana_final();
	system("exit");
}

void control::proceso_ven_calculadora() {

	//Sleep(8000);
}