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
        unsigned long int inseridos;
        long int hash1(long int k);
        long int hash2(long int k);

    public:
        long int agrupaChave(int k, Data data);
        Tabela();
        Tabela(int m);
        ~Tabela();
        long int hash(long int k, int i);
        long int insere(Registro registro);
        Registro busca(int codigo, string data);
        Registro buscaPorPosicao(long int posicao);
        string imprimir();
        void imprime();
        void escrever(string path);
        int totalDeCasos(int codigo);
};

#endif // TABELA_H