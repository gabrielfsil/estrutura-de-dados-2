#include "Ordena.h"
#include "Registro.h"

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

    if (fim - inicio > 0)
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
    int pivo = medianaDasMedianas(vet, inicio, fim);

    int i = inicio - 1;

    for (int j = inicio; j <= fim - 1; j++)
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

int Ordena::medianaDasMedianas(Registro vet[], int inicio, int fim)
{

    int meio = (inicio + fim) / 2;

    int mediana = vet[meio].getCasos();

    // Se o inicio está entre o meio e o fim | meio < inicio < fim | fim < inicio < meio
    if ((vet[inicio].getCasos() > mediana && vet[inicio].getCasos() < vet[fim].getCasos()) || (vet[inicio].getCasos() < mediana && vet[inicio].getCasos() > vet[fim].getCasos()))
    {
        numComparacao = numComparacao + 4;
        return inicio;
    }
    // Se o fim está entre o meio e o inicio | meio < fim < inicio| inicio < fim < meio
    else if ((vet[fim].getCasos() > mediana && vet[fim].getCasos() < vet[inicio].getCasos()) || (vet[fim].getCasos() < mediana && vet[fim].getCasos() > vet[inicio].getCasos()))
    {
        numComparacao = numComparacao + 4;
        return fim;
    }
    // Se o meio está entre o inicio e o fim | inicio < meio < fim | fim < meio < inicio
    else
    {

        return meio;
    }
}

void Ordena::troca(Registro vet[], int p, int q)
{

    Registro aux = vet[p];

    vet[p] = vet[q];
    vet[q] = aux;
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
