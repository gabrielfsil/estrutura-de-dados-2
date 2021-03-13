#include <iostream>
#include "ArvB.h"

using namespace std;

int main()
{
    int m = 3;
    ArvB * arv = new ArvB(m);

    cout << "Criando Arvore B" << endl;

    arv->insere(15);
    arv->insere(9);
    arv->insere(20);
    arv->insere(7);
    arv->insere(11);
    arv->insere(18);
    arv->insere(24);
    arv->insere(6);
    arv->insere(8);
    arv->insere(10);
    arv->insere(12);
    arv->insere(17);
    arv->insere(19);
    arv->imprime();

    cout << "Comparacoes: " << arv->getComparacoes() << endl;


    cout << "Busca o valor 20: ";
            if(arv->busca(20) != NULL)
            cout << "1" << endl;
            else
            cout << "0" << endl;

    cout << "Busca o valor 6: ";
                if(arv->busca(6) != NULL)
                cout << "1" << endl;
                else
                cout << "0" << endl;    cout << endl;


    system("pause");

    return 0;
}

