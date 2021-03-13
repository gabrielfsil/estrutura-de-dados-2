#ifndef ArvB_H_INCLUDED
#define ArvB_H_INCLUDED
#include "NoArvB.h"

class ArvB
{
public:
    ArvB(int m);
    ~ArvB();
    bool vazia(); // verifica se a �rvore est� vazia
    NoArvB* busca(int chave);
    void insere(int chave);
    void imprime();
    int getM();
    int getN();

   // void preencheABB(ArvB *a, int p, int q);
    //NoArvB* auxPreencheABB(NoArvB *a, int p, int q);




private:
    NoArvB* raiz; // ponteiro para o No raiz da �rvore
    int m;//grau minimo
    NoArvB* auxBusca(NoArvB *p, int chave);
    NoArvB* auxInsere(NoArvB *p, int chave);
    void auxImprime(NoArvB* p);
    NoArvB* libera(NoArvB *p);
    int n;
    void insereComEspaco(NoArvB *p, int chave);
    NoArvB * cisao(NoArvB * p);




};

#endif // ArvB_H_INCLUDED
