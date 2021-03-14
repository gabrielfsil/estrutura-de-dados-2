#include <iostream>
#include <fstream>
#include "ArvB.h"
#include "Registro.h"
#include "Tabela.h"
#include "Data.h"


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


void ArvB::insere(int val, Tabela * tabela)
{
    raiz = auxInsere(raiz, val, tabela);
}

NoArvB* ArvB::auxInsere(NoArvB *p, int chave, Tabela * tabela)
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
                //Busca o registro dado pela chave
                Registro regC = tabela->buscaPorPosicao(chave);

                //Transforma o codigo e data do registro em um inteiro que concatena as duas informações
                //Usaremos esse valor para comparação
                int valC = tabela->agrupaChave(regC.getCodigo(), regC.getData());

                //Fazemos o mesmo com o a chave da raiz
                //Busca o registro dado pela primeir chave do vetor de chaves do no q
                Registro regQ = tabela->buscaPorPosicao(q->getChaves()[0]);

                int valQ = tabela->agrupaChave(regQ.getCodigo(), regQ.getData());
                // if(q->getChaves()[0] < chave)

                if(valQ < valC)
                    i++;
                
                // cout << "inserindo em q->filhos[" << i <<"]" << endl;
                insereComEspaco(q->getFilhos()[i], chave,tabela);

             p = q;
        }
        else
        {

            //   cout <<  "numero de chaves no no: " << p->getN() << endl;
            //   cout << "Tem espaço!" << endl;
            insereComEspaco(p, chave, tabela);

        }
    }

    return p;
}

void ArvB::insereComEspaco(NoArvB * p, int chave, Tabela * tabela)
{
    int i = p->getN()-1;
    Registro regC = tabela->buscaPorPosicao(chave);
    int valC = tabela->agrupaChave(regC.getCodigo(), regC.getData());

    Registro regP = tabela->buscaPorPosicao(p->getChaves()[i]);
    int valP = tabela->agrupaChave(regP.getCodigo(), regP.getData());

    if(p->ehFolha())//se o nó é folha
    {
        //procura o local correto para inserção do nó
        //enquanto move as chaves menores para frente
         
        comparacoes++;
        // while ((i >= 0) && (p->getChaves()[i] > chave))
        while ((i >= 0) && (valP > valC))
        { 
                p->getChaves()[i+1] = p->getChaves()[i]; 
                i--; 
                comparacoes++;
                if(i>=0)
                {
                    regP = tabela->buscaPorPosicao(p->getChaves()[i]);
                    valP = tabela->agrupaChave(regP.getCodigo(), regP.getData());
                }

        } 
        // cout << "inserindo chave " << chave << endl;
        //insere a chave no local encontrado
        p->getChaves()[i+1] = chave;
        p->setN(p->getN()+1);
        
    }//se o nó não é folha procuramos o filho que pode receber a chave
    else{
        comparacoes++;

        // while((i >= 0) && (p->getChaves()[i] > chave)){
        while((i>=0) && (valP>valC)){
            comparacoes++;
            i--;
            if(i>=0)
            {
                regP = tabela->buscaPorPosicao(p->getChaves()[i]);
                valP = tabela->agrupaChave(regP.getCodigo(), regP.getData());
            }
        }
        comparacoes++;
        if(p->getFilhos()[i+1]->getN() == (2*m-1)) //se o filho estiver cheio
        {
            //faz a cisão do nó
            p->cisao(i+1, p->getFilhos()[i+1]);

            regP = tabela->buscaPorPosicao(p->getChaves()[i+1]);
            valP = tabela->agrupaChave(regP.getCodigo(), regP.getData());
            
            comparacoes++;
            //if(p->getChaves()[i+1]<chave)
            if(valP <valC)
                i++;
        }
        //se tiver espaço no filho insere a chave
        
            auxInsere(p->getFilhos()[i+1], chave, tabela);
    }
}
NoArvB * ArvB::busca(int chave, Tabela * tabela)
{
    return auxBusca(raiz, chave,tabela);
}

NoArvB * ArvB::auxBusca(NoArvB *p, int chave, Tabela * tabela)
{
    int i =0;

    Registro regC = tabela->buscaPorPosicao(chave);
    int valC = tabela->agrupaChave(regC.getCodigo(), regC.getData());

    Registro regP = tabela->buscaPorPosicao(p->getChaves()[i]);
    int valP = tabela->agrupaChave(regP.getCodigo(), regP.getData());

    comparacoes++;
    //while((i<p->getN()) && (p->getChaves()[i]<chave)){
    while((i<p->getN()) && (valP < valC)){
        
        comparacoes++;
        i++;
        if(i<p->getN())
        {
            regP = tabela->buscaPorPosicao(p->getChaves()[i]);
            valP = tabela->agrupaChave(regP.getCodigo(), regP.getData());
        }

    }
    regP = tabela->buscaPorPosicao(p->getChaves()[i]);
    valP = tabela->agrupaChave(regP.getCodigo(), regP.getData());

    comparacoes++;
    if(valP == valC)
    //if(p->getChaves()[i]==chave)
        return p;
    if (p->ehFolha())
        return NULL;
    return auxBusca(p->getFilhos()[i],chave, tabela);
}

void ArvB::imprime(Tabela * tabela)
{
    auxImprime(raiz, tabela);
    cout << endl;
}

void ArvB::auxImprime(NoArvB *p, Tabela * tabela)
{
      
    int i; 
    for (i = 0; i < p->getN(); i++) 
    { 
       
        if (p->ehFolha() == false) 
            auxImprime(p->getFilhos()[i],tabela); 
        Registro regP = tabela->buscaPorPosicao(p->getChaves()[i]);  
        cout << regP.getCodigo() << " | " << regP.getDataStr() << endl;
    } 
  
    if (p->ehFolha() == false) 
        auxImprime(p->getFilhos()[i],tabela);

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
