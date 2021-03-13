#include <iostream>
#include <fstream>
#include "ArvB.h"

using namespace std;

ArvB::ArvB(int m)
{
    raiz = NULL;
    this->m = m; //grau minimo
    comparacoes = 0;
}

ArvB::~ArvB()
{
}

int ArvB::getM()
{
    return m;
}

int ArvB::getComparacoes()
{
    return comparacoes;
}
bool ArvB::vazia()
{
    return raiz == NULL;
}

void ArvB::insere(int val)
{
    raiz = auxInsere(raiz, val);
}

NoArvB *ArvB::auxInsere(NoArvB *p, int chave)
{
    // cout << "inserindo chave "<< chave << endl;
    if (p == NULL)
    {
        // cout << "raiz é nula, raiz recebe " << chave << endl;
        p = new NoArvB(m, true);
        p->getChaves()[0] = chave;
        p->setN(1);
        raiz = p;
    }
    else
    {
        comparacoes++;
        if (p->getN() == (2 * m - 1)) //se não há espaço para chaves no nó
        {
            // cout <<  "numero de chaves no no: " << p->getN() << endl;
            //cout << "No cheio!" << endl;
            //cria no para ser a nova raiz
            NoArvB *q = new NoArvB(m, false);

            //raiz antiga p vira filha da nova raiz q

            // cout << "no p (raiz antiga) vira filho do no q" <<endl;
            q->getFilhos()[0] = p;

            //fazemos cisão na raiz antiga p e movemos uma chave para a nova raiz q

            //cout << "cisao no no p e movendo chave para q" << endl;
            q->cisao(0, p);

            //a nova raiz tem dois filhos, agora definimos ual filho receberá a chave
            int i = 0;

            // cout << "q->chaves[0] = " << q->getChaves()[0] <<endl;
            comparacoes++;
            if (q->getChaves()[0] < chave)
                i++;

            // cout << "inserindo em q->filhos[" << i <<"]" << endl;
            insereComEspaco(q->getFilhos()[i], chave);

            p = q;
        }
        else
        {

            //   cout <<  "numero de chaves no no: " << p->getN() << endl;
            //   cout << "Tem espaço!" << endl;
            insereComEspaco(p, chave);
        }
    }

    return p;
}

void ArvB::insereComEspaco(NoArvB *p, int chave)
{
    int i = p->getN() - 1;

    if (p->ehFolha()) //se o nó é folha
    {
        //procura o local correto para inserção do nó
        //enquanto move as chaves menores para frente
        comparacoes++;
        while ((i >= 0) && (p->getChaves()[i] > chave))
        {
            p->getChaves()[i + 1] = p->getChaves()[i];
            i--;
            comparacoes++;
        }
        // cout << "inserindo chave " << chave << endl;
        //insere a chave no local encontrado
        p->getChaves()[i + 1] = chave;
        p->setN(p->getN() + 1);

    } //se o nó não é folha procuramos o filho que pode receber a chave
    else
    {
        comparacoes++;
        while ((i >= 0) && (p->getChaves()[i] > chave))
        {
            comparacoes++;
            i--;
        }
        comparacoes++;
        if (p->getFilhos()[i + 1]->getN() == (2 * m - 1)) //se o filho estiver cheio
        {
            //faz a cisão do nó
            p->cisao(i + 1, p->getFilhos()[i + 1]);
            comparacoes++;
            if (p->getChaves()[i + 1] < chave)
                i++;
        }
        //se tiver espaço no filho insere a chave

        auxInsere(p->getFilhos()[i + 1], chave);
    }
}
NoArvB *ArvB::busca(int chave)
{
    return auxBusca(raiz, chave);
}

NoArvB *ArvB::auxBusca(NoArvB *p, int chave)
{
    int i = 0;
    comparacoes++;
    while ((i < p->getN()) && (p->getChaves()[i] < chave))
    {
        comparacoes++;
        i++;
    }
    comparacoes++;
    if (p->getChaves()[i] == chave)
        return p;
    if (p->ehFolha())
        return NULL;
    return auxBusca(p->getFilhos()[i], chave);
}

void ArvB::imprime()
{
    auxImprime(raiz);
    cout << endl;
}

void ArvB::auxImprime(NoArvB *p)
{

    int i;
    for (i = 0; i < p->getN(); i++)
    {

        if (p->ehFolha() == false)
            auxImprime(p->getFilhos()[i]);
        cout << " " << p->getChaves()[i];
    }

    if (p->ehFolha() == false)
        auxImprime(p->getFilhos()[i]);
}

void ArvB::imprimeArquivo(string filename)
{
    ofstream output(filename);

    auxImprimeArquivo(raiz, output);
    cout << endl;
}

void ArvB::auxImprimeArquivo(NoArvB *p, ofstream &output)
{

    int i;
    for (i = 0; i < p->getN(); i++)
    {

        if (p->ehFolha() == false)
            auxImprimeArquivo(p->getFilhos()[i], output);
        output << " " << p->getChaves()[i];
    }

    if (p->ehFolha() == false)
        auxImprimeArquivo(p->getFilhos()[i], output);
}

// NoArvB* ArvB::libera(NoArvB *p)
// {
//     if(p != NULL)
//     {
//         p->setEsq(libera(p->getEsq()));
//         p->setDir(libera(p->getDir()));
//         delete p;
//         p = NULL;
//     }
//     return p;
// }
