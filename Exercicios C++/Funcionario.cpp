#include <iostream>
#include "Funcionario.hpp"
using namespace std;

	string Funcionario::getnome(){
        return nome;
    }
	void Funcionario::setNome(string nome){
        this->nome=nome;
    }
    
	int Funcionario::getSalario(){
        return salario;
    }
	void Funcionario::setSalario(int salario){
        this->salario=salario;
    }

    string Funcionario::getDataAdm(){
        return dataAdm;
    }
	void Funcionario::setDataAdm(string DataAdm){
        this->dataAdm = DataAdm;
    }
