#include <iostream>
#include "AVL.h"

using namespace std;

int main()
{
    AVL * arv = new AVL();

    cout << "Criando Arvore AVL" << endl;
    arv->insere(15);
    arv->insere(9);
    arv->insere(20);
    arv->insere(7);
    arv->insere(11);
    arv->insere(18);
    arv->insere(24);
    arv->insere(6);
    arv->insere(8);
    // arv->insere(10);
    // arv->insere(12);
    // arv->insere(17);
    // arv->insere(19);
    arv->imprime();
    cout << endl;
    arv->imprimeInOrdem();

    cout << "Busca o valor 20: " << arv->busca(20) << endl;
    cout << "Busca o valor  5: " << arv->busca(5) << endl;

    cout << endl;




    system ("pause");
    return 0;
}

