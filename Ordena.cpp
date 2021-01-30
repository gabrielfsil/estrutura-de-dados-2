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

void Ordena::quicksort(Registro vet[], int inicio, int fim)
{

    if (inicio < fim)
    {
        // Retorna a posição do pivô já ordenado
        int q = particionamento(vet, inicio, fim);

        // Chama o algoritmo recursivamente para ordenar as outras duas partes do vetor
        quicksort(vet, inicio, q - 1);
        quicksort(vet, q + 1, fim);
    }
}

int Ordena::particionamento(Registro *vet, int inicio, int fim)
{

    // Escolha do Pivô
    medianaDasMedianas(vet, inicio, fim);
    int pivo = fim;

    int i = inicio - 1;

    for (int j = inicio; j <= fim; j++)
    {
        numComparacao++;
        if (vet[j].getCasos() < vet[pivo].getCasos())
        {
            i++;
            troca(vet, i, j);
            numTroca++;
        }
    }

    troca(vet, i + 1, fim);

    numTroca++;

    return (i + 1);
}

void Ordena::medianaDasMedianas(Registro vet[], int inicio, int fim)
{

    int meio = (inicio + fim) / 2;

    int casos_inicio = vet[inicio].getCasos();
    int casos_meio = vet[meio].getCasos();
    int casos_fim = vet[fim].getCasos();

    int mediana = 0;

    if (casos_inicio < casos_meio)
    {
        // Casos Inicio < Casos Meio < Casos Fim
        if (casos_meio < casos_fim)
        {
            mediana = meio;
        }
        // Casos Inicio < Casos Fim < Casos Meio
        else if (casos_inicio < casos_fim)
        {
            mediana = fim;
        }
        // Casos Meio < Casos Inicio <  Casos Fim
        else
        {
            mediana = inicio;
        }
    }
    else
    {
        // Casos Fim < Casos Meio < Casos Inicio
        if (casos_fim < casos_meio)
        {
            mediana = meio;
        }
        // Casos Meio < Casos Fim < Casos Inicio
        else if (casos_fim < casos_inicio)
        {
            mediana = fim;
        }
        // Casos Fim < Casos Inicio <  Casos Meio
        else
        {
            mediana = inicio;
        }
    }

    troca(vet, mediana, fim);
}

int Ordena::getNumComparacao()
{

    return numComparacao;
}

int Ordena::getNumTroca()
{

    return numTroca;
}

void Ordena::insertsort(Registro vet[], int n)
{

    for (int j = 2; j < n; j++)
    {

        Registro pivo = vet[j];
        int i = j - 1;

        while ((i > 0) && (vet[i].getCasos() > pivo.getCasos()))
        {
            vet[i + 1] = vet[i];
            i = i - 1;
        }

        vet[i + 1] = pivo;
    }
}

//Troca o conteudo de duas posições do vetor entre si
void Ordena::troca(Registro *vet, int p, int q)
{
    Registro aux = vet[p];
    vet[p] = vet[q];
    vet[q] = aux;
}

void Ordena::selectionSort(Registro *vet, int N)
{
    for (int i = 0; i < N; i++)
    {
        int min = i;

        for (int j = i + 1; j < N; j++)
        {
            if (vet[j].getCasos() < vet[min].getCasos())
            {
                this->numComparacao++;
                min = j;
            }
        }
        troca(vet, min, i);
        this->numTroca++;
    }
}

//Ordenação da etapa de pré-processamento dos dados pelo método de seleção
//onde a comparação para achar o valor mínimo leva 3 critérios, que são data, estado e cidade
void Ordena::selectionSortPre(Registro *registros, int N)
{

    string sigla, siglaMin, cidade, cidadeMin;
    int val1, val2;

    for (int i = 0; i < N; i++)
    {
        int min = i;

        for (int j = i + 1; j < N; j++)
        {
            if (registros[j].getData().compareTo(registros[min].getData()) == -1)
            {
                min = j;
            }
            else if (registros[j].getData().compareTo(registros[min].getData()) == 0)
            {
                sigla = registros[j].getSigla();
                siglaMin = registros[min].getSigla();

                if (sigla < siglaMin)
                {
                    min = j;
                }
                else if (sigla == siglaMin)
                {
                    cidade = registros[j].getCidade();
                    cidadeMin = registros[min].getCidade();
                    if (cidade < cidadeMin)
                    {
                        min = j;
                    }
                }
            }
        }

        troca(registros, min, i);
    }
}

void Ordena::merge(Registro *vet, int p, int q, int r)
{

    int i = p;
    int j = q;
    int k = 0;
    Registro *aux = new Registro[r];

    while ((i < q) && (j < r))
    {
        this->numComparacao++;
        if (vet[i].getCasos() < vet[j].getCasos())
        {
            aux[k] = vet[i];
            i++;
            ;
        }
        else
        {
            aux[k] = vet[j];
            j++;
            ;
        }
        k++;
    }
    while (i < q)
    {
        aux[k] = vet[i];
        i++;
        k++;
    }
    while (j < r)
    {
        aux[k] = vet[j];
        j++;
        k++;
    }

    for (int i = p; i < r; i++)
    {
        vet[i] = aux[i - p];
        this->numTroca++;
    }

    delete[] aux;
}

void Ordena::mergeSort(Registro *vet, int p, int r)
{
    this->numComparacao++;
    if (p < (r - 1))
    {
        int q = (p + r) / 2;
        mergeSort(vet, p, q);
        mergeSort(vet, q, r);
        merge(vet, p, q, r);
    }
}
