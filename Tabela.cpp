#include "Tabela.h"
#include <iostream>
#include "Data.h"
#include "Registro.h"

Tabela::Tabela()
{
}

Tabela::Tabela(int m)
{

    registros = new Registro[m];
    Tabela::m = m;
    mLinha = m - 2;
    colisoes = 0;
    erros = 0;
}

Tabela::~Tabela()
{

    delete[] registros;
}

long int Tabela::hash(long int k, int i)
{
    return (hash1(k) + hash2(k) * i) % m;
}

long int Tabela::hash1(long int k)
{
    return k % m;
}

long int Tabela::hash2(long int k)
{
    return (k % mLinha) + 1;
}

bool Tabela::insere(Registro registro)
{

    int i = 0;

    long int chave = agrupaChave(registro.getCodigo(), registro.getData());

    while (i < m)
    {

        int posicao = hash(chave, i);

        if (registros[posicao].getCidade() == "")
        {

            registros[posicao] = registro;
            return true;
        }

        i++;
        colisoes++;
    }

    erros++;
    return false;
}

long int Tabela::agrupaChave(int codigo, Data data)
{

    return codigo + ((10000 * data.getAno()) + (100 * data.getMes()) + data.getDia());
}

Registro Tabela::busca(int codigo, string data)
{

    Data dataFormatada = Data(data);

    long int chave = agrupaChave(codigo, dataFormatada);

    int i = 0;
    while (i < m)
    {

        int posicao = hash(chave, i);
        if (posicao < m)
            if (registros[posicao].getCidade() != "" && agrupaChave(registros[posicao].getCodigo(), registros[posicao].getData()) == chave)
            {

                return registros[posicao];
            }

        i++;
    }
    return Registro();
}

string Tabela::imprimir()
{

    cout << endl
         << "Tabela Hashing" << endl
         << "Colisões: " << colisoes << endl
         << "Erros de Inserção: " << erros << endl
         << endl;
    string saida;
    for (int i = 0; i < m; i++)
    {
        saida += "[" + to_string(i);
        saida += "] - " + registros[i].retornaEmString();
        saida += "\n";
        
    }

    return saida;
}