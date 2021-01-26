#include "Ordena.h"
#include "Registro.h"

#include <iostream>

using namespace std;


Ordena::Ordena()
{
    numTroca = 0;
    numComparacao = 0;
}

Ordena::~Ordena()
{
}

int Ordena::getNumComparacao()
{

    return numComparacao;
}

int Ordena::getNumTroca()
{

    return numTroca;
}


//Troca o conteudo de duas posições do vetor entre si
void troca(Registro *vet, int p, int q)
{
    Registro aux;
    aux = vet[p];
    vet[p] = vet[q];
    vet[q] = aux;

}

void Ordena::selectionSort(Registro *vet , int N)
{
    for (int i =0; i<N; i++)
    {
        int min = i;
        
        for(int j = i+1; j<N; j++)
        {
            if(vet[j].getCasos() < vet[min].getCasos())
            {
                this->numComparacao++;
                min = j;
            }
        }
        troca(vet, min, i );
        this->numTroca++;
    }
}

//Ordenação da etapa de pré-processamento dos dados pelo método de seleção 
//onde a comparação para achar o valor mínimo leva 3 critérios, que são data, estado e cidade
void Ordena::selectionSortPre(Registro *registros, int N){

    string sigla, siglaMin, cidade, cidadeMin;
    int val1, val2;

    for(int i=0; i<N; i++)
    {
        int min = i;

        for(int j = i+1; j<N; j++)
        { 
            if(registros[j].getData().compareTo(registros[min].getData()) == -1)
            {
                            min = j;
            }else if(registros[j].getData().compareTo(registros[min].getData()) == 0)
            {
                sigla= registros[j].getSigla();
                siglaMin = registros[min].getSigla();

                if(sigla < siglaMin)
                {
                    min = j;
                }else if (sigla == siglaMin)
                {
                    cidade = registros[j].getCidade();
                    cidadeMin= registros[min].getCidade();
                    if(cidade < cidadeMin)
                    {
                        min = j;
                    }    
                }
            }
            
        }
        
        troca(registros, min, i);
    }

}


void Ordena::merge(Registro * vet, int p, int q, int r){

    int i = p;
    int j = q;
    int k = 0;
    Registro *aux = new Registro[r];

    while((i<q) && (j<r))
    {
        this->numComparacao++;
        if(vet[i].getCasos() < vet[j].getCasos())
        {
            aux[k] = vet[i];
            i++;;
        }
        else
        {
            aux[k] = vet[j];
            j++;;
        }
        k++;
    }
    while(i<q)
    {
        aux[k] = vet[i]; i++;k++;
    }
    while(j<r)
    {
        aux[k] = vet[j]; j++;k++;
    }

    for(int i = p; i<r; i++)
    {   
        vet[i] = aux[i-p];
        this->numTroca++;

    }
    
    delete[] aux;
        
}

void Ordena::mergeSort(Registro * vet, int p, int r)
{
    this->numComparacao++;
    if(p < (r-1))
    {
        int q = (p+r)/2;
        mergeSort(vet, p ,q);
        mergeSort(vet, q ,r);
        merge(vet,p,q,r);
    }
}
