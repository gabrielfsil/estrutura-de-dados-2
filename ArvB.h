#ifndef ArvB_H_INCLUDED
#define ArvB_H_INCLUDED
#include "NoArvB.h"
#include "Tabela.h"


class ArvB
{
public:
    ArvB(int m);
    ~ArvB();
    bool vazia(); // verifica se a �rvore est� vazia
    NoArvB* busca(int chave, Tabela * tabela);
    void insere(int chave, Tabela * tabela);
    void imprime(Tabela * tabela);
    int getM();
    int getN();
    int getComparacoes();
    


   // void preencheABB(ArvB *a, int p, int q);
    //NoArvB* auxPreencheABB(NoArvB *a, int p, int q);




private:
    NoArvB* raiz; // ponteiro para o No raiz da �rvore
    int m;//grau minimo
    NoArvB* auxBusca(NoArvB *p, int chave, Tabela * tabela);
    NoArvB* auxInsere(NoArvB *p, int chave, Tabela * tabela);
    void auxImprime(NoArvB* p, Tabela * tabela);
    NoArvB* libera(NoArvB *p);
    int n;
    void insereComEspaco(NoArvB *p, int chave, Tabela * tabela);
    NoArvB * cisao(NoArvB * p);
    int comparacoes;




};

#endif // ArvB_H_INCLUDED
