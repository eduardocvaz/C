#ifndef _FUNCIONARIO_
#define _FUNCIONARIO_

#include <string>
using namespace std;

class Funcionario {
public:
    string nome;
    int salario;
    string dataAdm;

    	// Metodos de acesso
	string getnome();
	void setNome(string nome);
    
	int getSalario();
	void setSalario(int salario);

    string getDataAdm();
	void setDataAdm(string DataAdm);
};

#endif