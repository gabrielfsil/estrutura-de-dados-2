#ifndef ORDENA_H
#define ORDENA_H
#include <stdlib.h>
#include "Registro.h"

class Ordena
{

public:
    Ordena();
    ~Ordena();
    void quicksort(Registro vet[], int inicio, int fim);
    void insertsort(Registro vet[], int n);
    void selectionSortPre(Registro *registros, int N);
    void selectionSort(Registro *vet, int N);
    void quicksortPre(Registro vet[], int inicio, int fim);
    void mergeSort(Registro *vetor, int p, int r);
    void merge(Registro *vet, int p, int q, int r);
    int getNumTroca();
    int getNumComparacao();

private:
    int particionamento(Registro vet[], int inicio, int fim);
    void troca(Registro vet[], int p, int q);
    void medianaDeTres(Registro vet[], int inicio, int fim);
    int numTroca;
    int numComparacao;
    int particionamentoPre(Registro vet[], int inicio, int fim);
};

#endif // ORDENA_H