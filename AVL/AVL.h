#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
#include "NoAVL.h"

class AVL
{
public:
    AVL();
    ~AVL();
    bool vazia(); // verifica se a �rvore est� vazia
    bool busca(int val);
    void insere(int val);
    void imprime();
    void imprimeInOrdem();
    void preencheABB(AVL *a, int p, int q);
    NoAVL * rotSEsq(NoAVL *p);//rotação simples a esquerda
    NoAVL * rotSDir(NoAVL *p);//rotação simples a direita
    NoAVL * rotDEsq(NoAVL *p);//rotação dupla a esquerda
    NoAVL * rotDDir(NoAVL *p);//rotação dupla a direita
    int getComparacoes();


    //AVL* auxPreencheABB(AVL *a, int p, int q);




private:
    NoAVL* raiz; // ponteiro para o No raiz da �rvore
    bool auxBusca(NoAVL *p, int val);
    NoAVL* auxInsere(NoAVL *p, int val);
    void imprimePorNivel(NoAVL* p, int nivel);
    void auxInOrdem(NoAVL *p);
    NoAVL* libera(NoAVL *p);
    int h;
    int comparacoes;



};

#endif // AVL_H_INCLUDED
