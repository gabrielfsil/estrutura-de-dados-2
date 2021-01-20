#include <stdlib.h>
#include <iostream>
#include "Registro.h"
#include "Data.h"

using namespace std;

int main(int argc, char *argv[])
{


    Registro *registro = new Registro[10];

    for(int i = 0; i < 10; i++){

        registro[i] = Registro("2020-01-15" , "MG", "Felilândia", 59, 3, i);

    }

    for(int i = 0; i < 10; i++){

        registro[i].getData().imprimir();
        cout << " - " << registro[i].getCodigo() << " - " << registro[i].getCidade() << " - " << registro[i].getSigla() << endl;

    }
    
    delete[] registro;

    return 0;
};