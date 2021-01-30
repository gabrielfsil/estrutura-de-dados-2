#ifndef ORDENA_H
#define ORDENA_H
#include <stdlib.h>
#include "Registro.h"

class Ordena{

    public:
        Ordena();
        ~Ordena();
        void selectionSort(Registro *vet, int N);
        void quicksortPre(Registro vet[], int inicio, int fim);
        int getNumTroca();
        int getNumComparacao();
    
    private:
        int numTroca;
        int numComparacao;
         int particionamentoPre(Registro vet[], int inicio, int fim);
         void troca(Registro vet[], int p, int q);
};


#endif // ORDENA_H