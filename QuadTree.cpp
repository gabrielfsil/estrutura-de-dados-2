#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <stdlib.h>
#include "QuadTree.h"
#include "Cidade.h"

using namespace std;

QuadTree::QuadTree()
{
    raiz = NULL;
}

QuadTree::~QuadTree()
{
}

//Retorna o quadrante Q onde P está localizado no quadrante enraizado por R
int quadtree_compare(NoQuad *p, Cidade *cidade)
{
    // cout << "raiz: "<< p->getX() << " , " << p->getY()<< endl;
    // cout << "Cidade: " << cidade->getLat() << " , " << cidade->getLon()<< endl;

    if (cidade->getLat() < p->getX())
    {
        if (cidade->getLon() < p->getY())
            return 3; //SW;
        else
            return 2; // NW;
    }
    else if (cidade->getLon() < p->getY())
        return 4; // SE;
    else
        return 1; // NE;
}

void QuadTree::insere(Cidade *cidade)
{

    raiz = auxInsere(raiz, cidade);
}

NoQuad *QuadTree::auxInsere(NoQuad *P, Cidade *cidade)
{
    //Ponteiro Pai aponta para Raiz
    NoQuad *PAI;
    int Q;

    if (P == NULL) //Arvore vazia
    {
        P = new NoQuad();
        P->setInfo(cidade);
        P->setX(cidade->getLat());
        P->setY(cidade->getLon());
    }
    else if ((P->getX() != cidade->getLat()) && (P->getY() != cidade->getLon()))
    {
        Q = quadtree_compare(P, cidade);

        switch (Q)
        {
        case 1:
            P->setNE(auxInsere(P->getNE(), cidade));
            // cout << "NE da raiz: " << P->getNE()->getInfo()->getNomeCidade() << endl;

            break;
        case 2:
            P->setNW(auxInsere(P->getNW(), cidade));
            // cout << "NW da raiz: " << P->getNW()->getInfo()->getNomeCidade() << endl;
            break;
        case 3:
            P->setSW(auxInsere(P->getSW(), cidade));
            // cout << "SW da raiz: " << P->getSW()->getInfo()->getNomeCidade() << endl;
            break;
        case 4:
            P->setSE(auxInsere(P->getSE(), cidade));
            // cout << "SE da raiz: " <<P->getSE()->getInfo()->getNomeCidade() << endl;
            break;
        default:
            break;
        }
    }
    return P;
}

bool QuadTree::sameCoord(NoQuad *r, NoQuad *p)
{

    // cout << "R: " << "[" << r->getX()<< " , " << r->getY() << "]" << endl;
    // cout << "P: " << "[" << p->getX() <<" , " <<p->getY() << "]" << endl;

    if ((r->getX() == p->getX()) && (r->getY() == p->getY()))
        return true;
    return false;
}

bool QuadTree::busca(float X, float Y)
{
    return auxBusca(raiz, X, Y);
}

vector<Cidade *> QuadTree::buscaRange(float x0, float y0, float x1, float y1)
{
    vector<Cidade *> cidades;
    auxBuscaRange(raiz, &cidades, x0, y0, x1, y1);
    return cidades;
}

bool isInRange(NoQuad *p, float x0, float y0, float x1, float y1)
{
    if ((p->getX() >= x0) && (p->getX() <= x1) && (p->getY() >= y0) && (p->getY() <= y1))
        return true;
    return false;
}

vector<Cidade *> QuadTree::auxBuscaRange(NoQuad *p, vector<Cidade *> *cidades, float x0, float y0, float x1, float y1)
{

    if (p != NULL)
    {

        //Se encontramos nós e estão dentro do intervalo, adicionamos o nó equivalente a cidade
        //no vetor de cidades e buscamos por outros nós que podem estar no intervalo

        if (isInRange(p, x0, y0, x1, y1))
        {
            (*cidades).push_back(p->getInfo());
        }
        auxBuscaRange(p->getNE(), cidades, x0, y0, x1, y1);
        auxBuscaRange(p->getNW(), cidades, x0, y0, x1, y1);
        auxBuscaRange(p->getSW(), cidades, x0, y0, x1, y1);
        auxBuscaRange(p->getSE(), cidades, x0, y0, x1, y1);
    }
    return *cidades;
}

bool QuadTree::auxBusca(NoQuad *p, float X, float Y)
{
    //Se a árvore está vazia retorna falso
    if (p == NULL)
        return false;
    //Senão, se as coordenadas do nó forem iguais as coordenadas do Cidade que buscamos:
    if ((p->getX() == X) && (p->getY() == Y))
        //retornamos true
        return true;
    //Senão, se a coordenada X do Cidade buscado estiver a esquerda da raiz:
    if (X < p->getX())
    {
        //checamos a coordenada Y
        //Se a coordenada Y do Cidade buscado estiver a baixo da raiz:
        if (Y < p->getY())
            //Busca a partir do nó SW
            return auxBusca(p->getSW(), X, Y);
        else
            //Senão, busca a partir do nó NW
            return auxBusca(p->getNW(), X, Y);
    }
    //Senão,a coordenada X do Cidade que buscamos está a direita da raiz então checamos
    //se a coordenada Y está abaixo da raiz
    else if (Y < p->getY())
        //Se sim buscamos a partir do nó SE
        return auxBusca(p->getSE(), X, Y);
    //Senão buscamos a partir do nó NE
    else
        return auxBusca(p->getNE(), X, Y);
}

void QuadTree::imprime()
{
    imprimePorNivel(raiz, 0, "R");
}

void QuadTree::imprimePorNivel(NoQuad *p, int nivel, string Q)
{
    if (p != NULL)
    {
        if (nivel != 0)
            cout << setw(nivel * 2);

        cout << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            cout << "--";

        cout << p->getInfo()->getNomeCidade() << " [" << Q << "]" << endl;

        imprimePorNivel(p->getNE(), nivel + 1, "NE");
        imprimePorNivel(p->getNW(), nivel + 1, "NW");
        imprimePorNivel(p->getSW(), nivel + 1, "SW");
        imprimePorNivel(p->getSE(), nivel + 1, "SE");
    }
}

void QuadTree::imprimeArquivo(string filename)
{
    ofstream output(filename);

    imprimePorNivelArquivo(raiz, 0, "R", output);
}

void QuadTree::imprimePorNivelArquivo(NoQuad *p, int nivel, string Q, ofstream &file)
{
    if (p != NULL)
    {
        if (nivel != 0)
            file << setw(nivel * 2);

        file << "(" << nivel << ")";
        for (int i = 1; i <= nivel; i++)
            file << "--";

        file << p->getInfo()->getNomeCidade() << " [" << Q << "]" << endl;

        imprimePorNivelArquivo(p->getNE(), nivel + 1, "NE", file);
        imprimePorNivelArquivo(p->getNW(), nivel + 1, "NW", file);
        imprimePorNivelArquivo(p->getSW(), nivel + 1, "SW", file);
        imprimePorNivelArquivo(p->getSE(), nivel + 1, "SE", file);
    }
}

/*
void QuadTree::preencheABB(QuadTree *a, int p, int q)
{
    a->insere()
    if(q%2)
    val = q/2+1;
    else val = (q/2);
    a->insere(val)
    n = auxPreencheABB(n , p , q)
}*/
