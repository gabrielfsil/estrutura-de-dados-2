#include <iostream>
#include "AVL.h"

using namespace std;


AVL::AVL()
{
    raiz = NULL;
    comparacoes=0;
}


bool AVL::vazia()
{
    return raiz == NULL;
}


int altura(NoAVL *p)

{
    if(p==NULL)
        return -1;
    return p->getAltura();
}

int balancemento(NoAVL *p) 
{ 
    if (p == NULL) 
        return 0; 
    return altura(p->getDir()) - altura(p->getEsq()); 
} 

int maior (NoAVL *p, NoAVL *q)
{
    if(altura(p)>altura(q))
        return altura(p);
    return altura(q);
}

void AVL::insere(int chave)
{
    raiz = auxInsere(raiz, chave);
}

NoAVL* AVL::auxInsere(NoAVL *p, int chave)
{
    cout << "tentando inserir " << chave <<endl;
    if(p == NULL)
    {
        p = new NoAVL();
        p->setInfo(chave);
        p->setEsq(NULL);
        p->setDir(NULL);
        p->setAltura(0);
        return p;
    }
    else{

        cout << "raiz = "<< p->getInfo() <<endl;
        cout << "altura = " << altura(p) <<endl;

        cout << "chave= " << chave << endl;

        comparacoes++;
        if(chave < p->getInfo()){
            cout << "insere na esquerda" <<endl;
            p->setEsq(auxInsere(p->getEsq(), chave));

        }
        else {
            cout << "insere na direita" <<endl;
            p->setDir(auxInsere(p->getDir(), chave));

        }

    } 
    
    //atualiza altura do no
    p->setAltura(1+maior(p->getDir(), p->getEsq()));
    cout << "altura atualizada de " << p->getInfo() << " = " << altura(p) <<endl;


     int fatorB = balancemento(p);
     cout << "fator de balanceamento de " << p->getInfo() << "= "<< fatorB <<endl;

    //rotação simples a esqurda
        //se F(p) igual a 2 Q = nó a diretia
    if(fatorB ==2)
    {
        NoAVL * q = p->getDir();
        if((balancemento(q)== 1) || (balancemento(q) == 0)){//se f(q) == 1 ou 0
            cout << "rotação simples a esquerda na chave " << p->getInfo() << endl;
            return rotSEsq(p); //rotação simples a esquerda
        }
        if(balancemento(q) == -1){//se f(q) == -1 
            cout << "rotação dupla a esquerda na chave " << p->getInfo() << endl;

            return rotDEsq(p); //rotação dupla a esquerda
        }
    }
    if(fatorB == -2)
    {
        NoAVL * q = p->getEsq();
        if((balancemento(q) == -1) || (balancemento(q) == 0)){//se f(q) == -1 ou 0
            cout << "rotacao simples a direita na chave " << p->getInfo() << endl;
            return rotSDir(p); //rotação simples a direita
        }
        if(balancemento(q) == 1){//se f(q) == 1 
            cout << "rotação dupla a esquerda na chave " << p->getInfo() << endl;
            return rotDDir(p); //rotação dupla a direita
        }
    }

    return p;

}

bool AVL::busca(int chave)
{
    return auxBusca(raiz, chave);
}

bool AVL::auxBusca(NoAVL *p, int chave)
{
    if(p == NULL)
        return false;
    else{
        comparacoes++;
     if(p->getInfo() == chave)
        return true;

        else {
            comparacoes++;
            if(chave < p->getInfo())
            return auxBusca(p->getEsq(), chave);
        else
            return auxBusca(p->getDir(), chave);
        }
    }
}

NoAVL * AVL::rotSEsq(NoAVL *p)
{
    NoAVL * q = p->getDir();
    
    p->setDir(q->getEsq());
    q->setEsq(p);
    p->setAltura(1+maior(p->getDir(), p->getEsq()));
    q->setAltura(1+maior(q->getDir(), q->getEsq()));

    return q;
}
NoAVL * AVL::rotSDir(NoAVL *p)
{
    NoAVL * q = p->getEsq();
    p->setEsq(q->getDir());
    q->setDir(p);
    p->setAltura(1+maior(p->getDir(), p->getEsq()));
    q->setAltura(1+maior(q->getDir(), q->getEsq()));
    return q;
}

NoAVL * AVL::rotDEsq(NoAVL *p)
{
    NoAVL * q = p->getDir();
    NoAVL * r = q->getEsq();
    p->setDir(r->getEsq());
    q->setEsq(r->getDir());
    r->setEsq(p);
    r->setDir(q);
    p->setAltura(1+maior(p->getDir(), p->getEsq()));
    q->setAltura(1+maior(q->getDir(), q->getEsq()));
    r->setAltura(1+maior(r->getDir(), r->getEsq()));

    return r;
}

NoAVL * AVL::rotDDir(NoAVL *p)
{
    NoAVL * q = p->getEsq();
    NoAVL * r = q->getDir();
    p->setEsq(r->getDir());
    q->setDir(r->getEsq());
    r->setDir(p);
    r->setEsq(q);
    p->setAltura(1+maior(p->getDir(), p->getEsq()));
    q->setAltura(1+maior(q->getDir(), q->getEsq()));
    r->setAltura(1+maior(r->getDir(), r->getEsq()));
    return r;
}

AVL::~AVL()
{
    raiz = libera(raiz);
}

NoAVL* AVL::libera(NoAVL *p)
{
    if(p != NULL)
    {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = NULL;
    }
    return p;
}
void AVL::imprime()
{
    imprimePorNivel(raiz, 0);
}

void AVL::imprimePorNivel(NoAVL *p, int nivel)
{
    if(p != NULL)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->getInfo() << endl;
        imprimePorNivel(p->getEsq(), nivel+1);
        imprimePorNivel(p->getDir(), nivel+1);
    }
}

void AVL::imprimeInOrdem()
{
    auxInOrdem(raiz);
    cout << endl;
}
void AVL::auxInOrdem(NoAVL *p) 
{ 
    if(p != NULL) 
    { 
        auxInOrdem(p->getEsq()); 
        cout << p->getInfo() << " "; 
        auxInOrdem(p->getDir()); 
    } 
} 

int AVL::getComparacoes()
{
    return comparacoes;
}
// int altura(NoAVL * p)
//     {
//       int hesq, hdir;
//       if(p == NULL)
//           return -1;
//       hesq = altura(p->getEsq());
//       hdir = altura(p->getDir());

//       if(hesq > hdir)
//           return hesq + 1;
//       else
//           return hdir + 1;

//    }