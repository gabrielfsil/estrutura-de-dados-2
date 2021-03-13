#ifndef TABELA_H
#define TABELA_H
#include <stdlib.h>
#include "Data.h"
#include "Registro.h"
#include <string>


class Tabela
{
    private:
        Registro* registros;
        unsigned long int colisoes;
        unsigned long int erros;
        unsigned long int m;
        unsigned long int mLinha; 
        long int agrupaChave(int k, Data data);
        long int hash1(long int k);
        long int hash2(long int k);

    public:
        Tabela();
        Tabela(int m);
        ~Tabela();
        long int hash(long int k, int i);
        bool insere(Registro registro);
        Registro busca(int codigo, string data);
        string imprimir();
        void escrever(string path);
};

#endif // TABELA_H