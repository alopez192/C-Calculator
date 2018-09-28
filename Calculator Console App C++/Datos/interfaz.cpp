#include"interfaz.h"
#include <iostream>


void interfaz::ventana_inicio() {
	cout << "\n\t\t======================================" << endl;
	cout << "\n\t\t-------------BIENVENIDO---------------" << endl;
	cout << "\n\t\t-------APLLICACION CALCULADORA--- ----" << endl;
	cout << "\n\t\t======================================" << endl;
}
int interfaz::ventana_menu() {
	int opcion;
	cout << "\n\t\t=================================" << endl;
	cout << "\n\t\t---------   MENU    -------------" << endl;
	cout << "\n\t\t=================================" << endl;
	cout << "\n\t\t= 1- Hacer Calculos             =" << endl;
	cout << "\n\t\t= 2- Ver Expresion Posfija      =" << endl;
	cout << "\n\t\t= 3- ver Resultado              =" << endl;
	cout << "\n\t\t= 4- Salir                      =" << endl;
	cout << "\n\t\t=================================" << endl;
	cout << "\n\t\tDigite la opcion...";
	cin >> opcion;
	cout << endl << endl;
	system("cls");
	while (opcion < 1 || opcion >4) {
		cout << "\n\t\tERROR DIGITANDO OPCION" << endl;
		cout << "\n\t\tDIGITE UN VALOR ENTRE 1 Y 4" << endl;
		//Sleep(2000);
		system("cls");
		opcion = ventana_menu();
	}
	return opcion;
}
void interfaz::actualizar(){


}
string interfaz::ventana_calculadora(string s) {

	string vec[30];

	vec[0] = "\n\t\t==============================";
	vec[1] = "\n\t\t=|      ";
	vec[2] = "       ";
	vec[3] = "    ";
	vec[4] = s;
	vec[5] = "\n\t\t=     ";
	vec[6] = "        ";
	vec[7] = "       ";
	vec[8] = "[  AC  ]=";
	vec[9] = "\n\t\t=[  ^  ]";
	vec[10] = "[  /  ]";
	vec[11] = "[  9  ]";
	vec[12] = "[  8  ]=";
	vec[13] = "\n\t\t=[  7  ]";
	vec[14] = "[  6  ]";
	vec[15] = "[  5  ]";
	vec[16] = "[  4  ]=";
	vec[17] = "\n\t\t=[  3  ]";
	vec[18] = "[  2  ]";
	vec[19] = "[  1  ]";
	vec[20] = "[  0  ]=";
	vec[21] = "\n\t\t=[  *  ]";
	vec[22] = "[  -  ]";
	vec[23] = "[  +  ]";
	vec[24] = "[  =  ]=";
	vec[25] = "\n\t\t=============================\n";


	for (int i = 0, n = 0; i < 30; i++, n++){
		cout << vec[i];
		if (n == 4){
			cout << endl;
			n = 0;
		}
	}

	return "";
}


void interfaz::ventana_exp_posfija() {
	cout << endl << endl;
	cout << "\n\t\t======================================" << endl;
	cout << "\n\t\t====== EXPRESION POSFIJA ES = ========" << endl;
	cout << endl;
}

void interfaz::ventana_final(){
	system("cls");
	cout << endl << endl;
	cout << "\n\t\t=====================================" << endl;
	cout << "\n\t\t==== M U C H A S   G R A C I A S ====" << endl;
	cout << "\n\t\t-------------------------------------" << endl;
}

void interfaz::ven_ver_resultado() {
	cout << endl << endl;
	cout << "\n\t\t=======================================" << endl;
	cout << "\n\t\t====== EL RESULTADO ES ================" << endl;
	cout << endl;
}
