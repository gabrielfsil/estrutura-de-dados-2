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

    // cout << "inicio: " << inicio <<  " valor: " << vet[inicio].getCasos() << 
    // " | fim: " << fim  << " valor: "<< vet[fim].getCasos() << endl;

    // cout << "Mediana de tres" << endl;
    // // // Escolha do Pivô
    medianaDeTres(vet, inicio, fim);
    // cout << "inicio: " << inicio <<  " valor: " << vet[inicio].getCasos() << 
    // " | fim: " << fim  << " valor: "<< vet[fim].getCasos() << endl;
    
    int pivo = fim;

    cout<< "Indice pivo: [" << pivo << "] Valor pivo: " << vet[pivo].getCasos() << endl;


    // int i = inicio - 1;

    // for (int j = inicio; j <= fim - 1; j++)
    // {
    //     numComparacao++;
    //     if (vet[j].getCasos() < vet[pivo].getCasos())
    //     {
    //         i++;
    //         troca(vet, i, j);
    //         numTroca++;
    //     }
    // }

    // troca(vet, i + 1, fim);

    // numTroca++;

    // return (i + 1);
        // Escolha do Pivô
   // int pivo = fim;

    int i = inicio - 1;
      for(int k =0; k<=fim ; k++)
    {
        cout<< vet[k].getCasos() << "  ";
    }
    cout << endl;

    // Percorre o vetor até os indices se encontrarem
    for (int j = inicio; j <= fim - 1; j++)
    {
        // If current element is smaller than the pivot
        if (vet[j].getCasos() < vet[pivo].getCasos())
        {
            i++; // increment index of smaller element
            troca(vet, i, j);
        }
    }

    troca(vet, i + 1, fim);

    for(int k =0; k<=fim ; k++)
    {
        cout<< vet[k].getCasos() << "  ";
    }
    cout << endl;
    return (i + 1);
}

void Ordena::medianaDeTres(Registro vet[], int inicio, int fim)
{

    int meio = (inicio + fim) / 2;

    cout << "Meio indice: " << meio << " valor: " << vet[meio].getCasos() << endl;
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

    cout << "Mediana indice: " << mediana << " valor: " << vet[mediana].getCasos() << endl;
    troca(vet, mediana, fim);
    numTroca++;
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

    for (int j = 1; j < n; j++)
    {

        Registro pivo = vet[j];
        int i = j - 1;

        numComparacao++;
        while ((i >= 0) && (vet[i].getCasos() > pivo.getCasos()))
        {
            numTroca++;
            numComparacao++;
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
            this->numComparacao++;
            if (vet[j].getCasos() < vet[min].getCasos())
            {
                min = j;
            }
        }
        troca(vet, min, i);
        this->numTroca++;
    }
}

void Ordena::quicksortPre(Registro vet[], int inicio, int fim)
{

    if (inicio < fim)
    {
        // Retorna a posição do pivô já ordenado
        int q = particionamentoPre(vet, inicio, fim);

        // Chama o algoritmo recursivamente para ordenar as outras duas partes do vetor
        quicksortPre(vet, inicio, q - 1);
        quicksortPre(vet, q + 1, fim);
    }
}

bool iMenorQuePivo(Registro *registros, int i, int pivo)
{
    string sigla, siglaPivo, cidade, cidadePivo;

    if (registros[i].getData().compareTo(registros[pivo].getData()) == -1)
    {
        return true;
    }
    else if (registros[i].getData().compareTo(registros[pivo].getData()) == 0)
    {
        sigla = registros[i].getSigla();
        siglaPivo = registros[pivo].getSigla();

        if (sigla < siglaPivo)
        {
            return true;
        }
        else if (sigla == siglaPivo)
        {
            cidade = registros[i].getCidade();
            cidadePivo = registros[pivo].getCidade();
            if (cidade < cidadePivo)
            {
                return true;
            }
            return false;
        }
        return false;
    }
    return false;
}

int Ordena::particionamentoPre(Registro *vet, int inicio, int fim)
{

    // Escolha do Pivô
    int pivo = fim;

    int i = inicio - 1;

    // Percorre o vetor até os indices se encontrarem
    for (int j = inicio; j <= fim - 1; j++)
    {
        // If current element is smaller than the pivot
        if (iMenorQuePivo(vet, j, pivo))
        {
            i++; // increment index of smaller element
            troca(vet, i, j);
        }
    }

    troca(vet, i + 1, fim);
    return (i + 1);
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
