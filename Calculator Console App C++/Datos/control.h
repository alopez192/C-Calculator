#pragma once
#include "expression_handler.h"
#include <time.h>
using namespace std;
#include <string>


class control {
private:
    expression_handler* expression_handl;

public:
	control();
	~control();

	void proceso_inicio();
	void control_inicio();
	void proceso_ver_resultado();
	void proceso_exp_posfija();
	void proceso_ven_calculadora();
	void proceso_final();
	void hacer_calculos();
	void calcula_pos();
	void calcula_result();
};