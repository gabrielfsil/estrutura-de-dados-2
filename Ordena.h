#ifndef ORDENA_H
#define ORDENA_H
#include <stdlib.h>
#include "Registro.h"

class Ordena{

    public:
        Ordena();
        ~Ordena();
        void quicksort(Registro vet[], int inicio, int fim);
        int getNumTroca();
        int getNumComparacao();
    
    private:
        int particionamento(Registro vet[], int inicio, int fim);
        void troca(Registro vet[], int p, int q);
        int medianaDasMedianas(Registro vet[], int inicio, int fim);
        int numTroca;
        int numComparacao;
};


#endif // ORDENA_H