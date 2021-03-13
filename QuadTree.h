#ifndef QuadTree_H_INCLUDED
#define QuadTree_H_INCLUDED
#include "NoQuad.h"
#include "Cidade.h"

class QuadTree
{
public:
    QuadTree();
    ~QuadTree();
    bool vazia();
    bool busca(float X, float Y);
    void insere(Cidade *Cidade);
    void imprime();
    void imprimeArquivo(string filename);
    bool sameCoord(NoQuad *r, NoQuad *p);
    vector<Cidade *> buscaRange(float x0, float y0, float x1, float y1);

private:
    NoQuad *raiz; // ponteiro para o No raiz da arvore
    bool auxBusca(NoQuad *p, float X, float Y);
    void imprimePorNivel(NoQuad *p, int nivel, string R);
    void imprimePorNivelArquivo(NoQuad *p, int nivel, string R, ofstream &file);
    NoQuad *auxInsere(NoQuad *P, Cidade *Cidade);
    vector<Cidade *> auxBuscaRange(NoQuad *p, vector<Cidade *> *cidades, float x0, float y0, float x1, float y1);
};

#endif // QuadTree_H_INCLUDED
