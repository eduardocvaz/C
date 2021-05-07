#ifndef _EMPRESA_
#define _EMPRESA_

#include <string>
#include "Funcionario.hpp"

using namespace std;

class Empresa {
private:
	string nome;
	string CNPJ;
	int funcionarios;
	Funcionario* funcionario[10];
public:
	string getNomeEmpresa();
	string getCPNJ();
	Funcionario* getFuncionario(int numero);
	void setNomeEmpresa(string nome);
	void setCNPJ(string CNPJ);
	void Addfuncionario(Funcionario* novo);


};



#endif