#ifndef QuadTree_H_INCLUDED
#define QuadTree_H_INCLUDED
#include "NoQuad.h"
#include "Registro.h"

class QuadTree
{
public:
    QuadTree();
    ~QuadTree();
    bool vazia(); 
    bool busca(float X, float Y);
    void insere(Registro * registro);
    void imprime();
    bool sameCoord(NoQuad * r, NoQuad *p);
    vector <Registro*> buscaRange(float x0, float y0, float x1, float y1);

 
   // void preencheABB(QuadTree *a, int p, int q);
    //NoQuad* auxPreencheABB(NoQuad *a, int p, int q);




private:
    NoQuad* raiz; // ponteiro para o No raiz da arvore
    bool auxBusca(NoQuad *p, float X, float Y);
    void imprimePorNivel(NoQuad* p, int nivel, string R);
    NoQuad * auxInsere( NoQuad * P, Registro * registro);
    vector <Registro*>auxBuscaRange(NoQuad *p, vector <Registro*> * cidades,float x0, float y0, float x1, float y1);



};

#endif // QuadTree_H_INCLUDED
