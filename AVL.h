#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
#include "NoAVL.h"
#include "Tabela.h"

class AVL
{
public:
    AVL();
    ~AVL();
    bool vazia(); // verifica se a �rvore est� vazia
    bool busca(long int chave, Tabela * tabela);
    void insere(long int chave,Tabela * tabela);
    void imprime(Tabela * tabela);
    void imprimeInOrdem(Tabela * tabela);
    void preencheABB(AVL *a, int p, int q);
    NoAVL * rotSEsq(NoAVL *p);//rotação simples a esquerda
    NoAVL * rotSDir(NoAVL *p);//rotação simples a direita
    NoAVL * rotDEsq(NoAVL *p);//rotação dupla a esquerda
    NoAVL * rotDDir(NoAVL *p);//rotação dupla a direita
    int getComparacoes();


    //AVL* auxPreencheABB(AVL *a, int p, int q);




private:
    NoAVL* raiz; // ponteiro para o No raiz da �rvore
    bool auxBusca(NoAVL *p, long int chave, Tabela * tabela);
    NoAVL* auxInsere(NoAVL *p, long int chave,Tabela * tabela);
    void imprimePorNivel(NoAVL* p, int nivel, Tabela * tabela);
    void auxInOrdem(NoAVL *p, Tabela * tabela);
    NoAVL* libera(NoAVL *p);
    int h;
    int comparacoes;



};

#endif // AVL_H_INCLUDED
