#include <chrono>
#include <bits/stdc++.h>
#include <stdlib.h>

#include "Registro.h"
#include "Data.h"
#include "Ordena.h"
#include "Tabela.h"
#include "QuadTree.h"
#include "AVL.h"
#include "ArvB.h"

using namespace std;

void imprimeInformacoes(Registro *registros, int N)
{
    cout << "Informacoes armazenadas no arquivo:\n\n***" << endl;

    //Percorre os registros salvos e as informações de cada coluna (dado) referente ao mesmo
    for (int i = 1; i < N; i++)
    {
        cout << "Registro " << i << endl;
        cout << "Data: " << registros[i].getDataStr() << endl;
        cout << "Sigla: " << registros[i].getSigla() << endl;
        cout << "Cidade: " << registros[i].getCidade() << endl;
        cout << "Codigo: " << registros[i].getCodigo() << endl;
        cout << "Casos: " << registros[i].getCasos() << endl;
        cout << "Mortes: " << registros[i].getMortes() << endl;
        cout << endl;
    }
    cout << "\n***" << endl;
}
// Lê uma linha de registro da tabela e separa os dados das 6 colunas em um array com a quantidade de colunas
//e de acordo com o separador
//O array é de strings
//
void split(string str, char separator, vector<string> &splits)
{
    string split;
    std::stringstream ss;
    ss.str(str);
    while (getline(ss, split, ','))
    {
        //Adiciona cada string ao vetor de strings
        splits.push_back(split);
    }

    // " 2020-03-27,AC,Acrelândia,120001.0,0,0 "
    // array[0] = "2020-03-27"
    // array[1] = "AC"
    // array[2] = "Acrelândia"
    // array[3] = "120001.0"
    // array[4] = 0
    // array[5] = 0

    return;
}

//Função para embaralhar os registros que vem ordenados
void shuffle(Registro *registro, int tamanho)
{
    srand(time(NULL));
    for (int i = 0; i < tamanho; i++)
    {
        int r = rand() % tamanho;

        Registro *auxiliar = new Registro();
        *auxiliar = registro[i];
        registro[i] = registro[r];
        registro[r] = *auxiliar;
    }
}

// Leitura do arquivo brazil_covid19_cities_processado.csv e armazena em uma tabela hash
void leituraDeCasos(string path, Tabela *tabela, int tamanho)
{
    // string completePath = path + "teste-processado-10.csv";
    string completePath = path + "/brazil_covid19_cities_processado.csv";

    ifstream myfile(completePath);
    string line;
    vector<string> dados;
    int i = 0;
    if (myfile.is_open())
    {

        while (!myfile.eof())
        {
            getline(myfile, line);
            //Pula a primeira linha
            if (i != 0)
            {
                //Divide as informações da linha em vetores de string
                //esses são os dados que constituirão o registro
                split(line, ',', dados);

                Registro registro;

                registro.setData(dados[0]);
                registro.setSigla(dados[1]);
                registro.setCidade(dados[2]);
                registro.setCodigo(stoi(dados[3]));
                registro.setCasos(stoi(dados[4]));
                registro.setMortes(stoi(dados[5]));

                tabela->insere(registro);

                //Limpa o vetor dos dados da linha para reuso
                dados.clear();
                if (i >= tamanho)
                {

                    return;
                }
            }
            i++;
        }
    cout << "qtd registros: " << i << endl;

        myfile.close();
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}
//Função para colher conjunto de N registros aleatórios do arquivo
Registro *randomReg(Registro *registros, int N)
{
    //Vetor auxiliar para servir de contador se um valor gerado pela função rand
    //já apareceu, é inicializado com zero.

    int *aux = new int[N]();
    Registro *vet = new Registro[N];

    //Uso do srand para variar os números dados na função rand em cada execução
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        int num = rand() % N;

        while ((num < 0) || (aux[num] != 0))
        {
            num = rand() % N;
        }
        vet[i] = registros[num];
        aux[num] = 1;
    }
    delete[] aux;
    return vet;
}

int main(int argc, char *argv[])
{
    int n = 10;
    Tabela *tabela = new Tabela(n * 15);


    cout << "Lendo arquivo..." << endl;
    leituraDeCasos(argv[1], tabela, n);
    cout << "Leitura concluída!" << endl;
    Registro * registros = tabela->getRegistros();


    AVL *arvAVL = new AVL();

    cout << "Criando Arvore AVL" << endl;

    int i = 0;

    srand(time(NULL));
    while (i < n)
    {
        int num = rand() % n;

        arvAVL->insere(num, tabela);

        i++;
    }

    arvAVL->imprime(tabela);
    cout << endl;
    arvAVL->imprimeInOrdem(tabela);


    system("pause");
    return 0;
}