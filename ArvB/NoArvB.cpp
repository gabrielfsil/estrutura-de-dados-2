#include "NoArvB.h"
#include <iostream>

#include <stdlib.h>

using namespace std;



NoArvB::NoArvB(int m, bool folha) { 
    this->m =m;
    this->folha = folha;
    chaves = new int[2*m-1];
    filhos = new NoArvB*[2*m];
    n = 0;
}

NoArvB::~NoArvB(){ }


int * NoArvB::getChaves()
{
    return chaves;
}
void NoArvB::setM(int val)
{
    m = val;
}
int NoArvB::getM()
{
    return m;
}
void NoArvB::setN(int val)
{
    n = val;
}
int NoArvB::getN()
{
    return n;
}
void NoArvB::setFolha(bool val)
{
    folha = val;
}
bool NoArvB::ehFolha()
{
    return folha;
}

int NoArvB::getId(int pos)
{   
    return chaves[pos];
}

void NoArvB::addFilho(NoArvB * filho)
{
    filhos[n-1] = filho;
}
NoArvB** NoArvB::getFilhos()
{
    return filhos;
}

void NoArvB::cisao(int i, NoArvB *p)
{
   // novo nó para guardar metade das chaves de p;
    NoArvB *r = new NoArvB(p->getM(), p->ehFolha()); 
    r->setN(m-1);
  
    // copia de metade das chaves de p para o nó r
    for (int j = 0; j < m-1; j++) 
        r->getChaves()[j] = p->getChaves()[j+m]; 
  
    // copia da metade dos filhos de p para r (m)
    if (!p->ehFolha()) 
    { 
        for (int j = 0; j < m; j++) 
            r->getFilhos()[j] = p->getFilhos()[j+m]; 
    } 
  
    // nó p perde metade das chaves
    p->setN(m-1); 
  
    // o nó que chama a cisão receberá um novo filho
    //então liberamos espaço para ele
    for (int j = n; j >= i+1; j--) 
        filhos[j+1] = filhos[j]; 
  
    // insere o filho na posição liberada
    filhos[i+1] = r; 
  
    // uma chave de p será movida para o nó q
    //então encontramos o local para inserção
    for (int j = n-1; j >= i; j--) 
        chaves[j+1] = chaves[j]; 
  
    // chave central do conjunto é promovida a raiz
    //neste ponto (i=0)
    chaves[i] = p->getChaves()[m-1]; 

    //os filhos dessa raiz são os nós r e p
  
    //incrementa o número de chaves
    n = n + 1; 
}