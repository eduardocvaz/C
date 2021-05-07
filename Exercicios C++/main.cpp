#include <iostream>
#include "Empresa.hpp"
#include "Funcionario.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Funcionario fernandinho;
    fernandinho.setNome("fernando");
    Empresa shimagic;
    shimagic.setCNPJ("87812399123");
    //Addfuncionario(&fernandinho);

    cout << fernandinho.getnome() << endl;
    cout << shimagic.getCPNJ() << endl;

    return 0;
}

