#include <iostream>
#include "Empresa.hpp"

using namespace std;


    //EMPRESA


    string Empresa::getNomeEmpresa(){
        return nome;
    }
	string Empresa::getCPNJ(){
        return CNPJ;
    }
	Funcionario* Empresa::getFuncionario(int numero){
        return funcionario[numero];
    }
    
	void Empresa::setNomeEmpresa(string nome){
        this->nome=nome;
    }
	void Empresa::setCNPJ(string CNPJ){
        this->CNPJ=CNPJ;
    }
	void Empresa::Addfuncionario(Funcionario* novo){
		this->funcionario[this->funcionarios++] = novo;
    }