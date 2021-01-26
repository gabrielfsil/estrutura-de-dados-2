#ifndef ORDENA_H
#define ORDENA_H
#include <stdlib.h>
#include "Registro.h"

class Ordena{

    public:
        Ordena();
        ~Ordena();
        void selectionSortPre(Registro *registros, int N);
        void selectionSort(Registro *vet, int N);
        int getNumTroca();
        int getNumComparacao();
    
    private:
        int numTroca;
        int numComparacao;
};


#endif // ORDENA_H