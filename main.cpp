#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <bits/stdc++.h>
#include <stdlib.h>

#include "Registro.h"
#include "Data.h"
#include "Ordena.h"

using namespace std;
using namespace std::chrono;

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

void geraCSV(Registro *registros, int N, string filename)
{
    ofstream arq(filename);

    arq << "Data,Estado,Nome,Codigo,Casos/Dia,Mortes" << endl;

    for (int i = 0; i < N; i++)
    {

        arq << registros[i].getDataStr() << ",";
        arq << registros[i].getSigla() << ",";
        arq << registros[i].getCidade() << ",";
        arq << registros[i].getCodigo() << ",";
        arq << registros[i].getCasos() << ",";
        arq << registros[i].getMortes() << "" << endl;
    }

    arq.close();
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

//Função para leitura do arquivo processado
int leArquivoProcessado(Registro *registros, string fileDirectory)
{
    ifstream myfile(fileDirectory);
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

                registros[i - 1].setData(dados[0]);
                registros[i - 1].setSigla(dados[1]);
                registros[i - 1].setCidade(dados[2]);
                registros[i - 1].setCodigo(stoi(dados[3]));
                registros[i - 1].setCasos(stoi(dados[4]));
                registros[i - 1].setMortes(stoi(dados[5]));

                //Limpa o vetor dos dados da linha para reuso
                dados.clear();
            }
            i++;
        }
        shuffle(registros, i - 1);
        return i - 1;

        myfile.close();
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
    return 0;
}

//Função para leitura do arquivo em função da quantidade N de registros desejados
int processaCsv(Registro *registros, string fileDirectory, map<int, int> &registrosPorCidade)
{
    ifstream myfile(fileDirectory);
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

                registros[i - 1].setData(dados[0]);
                registros[i - 1].setSigla(dados[1]);
                registros[i - 1].setCidade(dados[2]);
                registros[i - 1].setCodigo(stoi(dados[3]));
                registros[i - 1].setCasos(stoi(dados[4]));
                registros[i - 1].setMortes(stoi(dados[5]));

                //Limpa o vetor dos dados da linha para reuso
                dados.clear();
                int codigoCidade = registros[i - 1].getCodigo();

                //Checa se no vetor existe a chave de mesmo código que o do registro
                if (registrosPorCidade.find(codigoCidade) == registrosPorCidade.end())
                {
                    //Se não, ele cria a chave e adiciona 1 registro a ela
                    registrosPorCidade.insert(make_pair(codigoCidade, 1));
                }
                else
                {
                    //Se já existe incrementa o  número de registros da cidade
                    registrosPorCidade[codigoCidade]++;
                }
            }
            i++;
        }
        shuffle(registros, i - 1);
        return i - 1;

        myfile.close();
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
    return 0;
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

//Função para separar o cumulativo de casos nas cidades em casos por dia
//O vetor de registros é percorrido de trás para frente e escolhendo uma cidade
//é checado se a mesma possui mais de um registro, se sim o algoritmo busca pela primeira
//cidade seguinte a ele, então é descontado dos casos do registro atual o valor de casos
//do seu próximo.
void totalDiario(Registro *registros, int N, map<int, int> &registrosPorCidade)
{

    for (int i = N - 1; i > 0; i--)
    {
        int j = i - 1;

        //Se a cidade possui mais de um registro sobre ela
        if (registrosPorCidade[registros[i].getCodigo()] > 1)
        {
            //Percorre os registros até achar o próximo registro que possua o mesmo código de cidade
            while ((registros[i].getCodigo() != registros[j].getCodigo()) && j > 0)
                j--;
            if ((registros[i].getCodigo() == registros[j].getCodigo()) && (registros[i].getCodigo() > registros[j].getCodigo()))
                registros[i].setCasos(registros[i].getCasos() - registros[j].getCasos());
        }
    }
}

int main(int argc, char *argv[])
{

    //PARA EXECUÇÃO DE TESTES PELO PROFESSOR
    //SE HABILITADO NÃO EXECUTAR O CÓDIGO DE IMPLEMENTAÇÃO COMPLETA DO TRABALHO
    int saida;
    cout << "=====Modulo de testes=====" << endl;
    cout << "Digite 1 se deseja exibir o resultado no console"<< endl;
    cout << "Digite 2 se deseja o resultado num arquivo"<< endl;
    cin >> saida;

    int opcao;
    cout << "Escolha uma das opcoes de teste" << endl;
    cout << "1 - Pre-Processamento" << endl;
    cout << "2 - Importacão de N registros aleatorios" << endl;
    cout << "3 - Ordencao Metodo Insercao " << endl;
    cout << "4 - Ordenacao Metodo Selecao  " << endl;
    cout << "5 - Ordenacao QuickSort " << endl;
    cout << "6 - Ordenacao MergeSort " << endl;
    cin >> opcao;

    
    Registro *registros = new Registro[1500000];
    cout << "Lendo registros" << endl;

    if(opcao==1)
    {
        //Vetor do tipo key value para servir do contador de registros por cidade
        map<int,int> registrosPorCidade ;
        int qtdRegistros = processaCsv(registros, argv[1], registrosPorCidade);

    }
    else{
        leArquivoProcessado(registros, argv[1]);
    }
    Ordena *ord = new Ordena();

    // Modulo de testes
    
    switch(opcao)
    {
        case 1 :
                if(saida==1){
                    //Vetor do tipo key value para servir do contador de registros por cidade
                    map<int,int> registrosPorCidade ;
                    int qtdRegistros = processaCsv(registros, argv[1], registrosPorCidade);
                    ord->quicksortPre(registros, 0, qtdRegistros);
                    totalDiario(registros, qtdRegistros, registrosPorCidade);
                    imprimeInformacoes(registros,10);
                }
                else{
                    //Vetor do tipo key value para servir do contador de registros por cidade
                    map<int,int> registrosPorCidade ;
                    int qtdRegistros = processaCsv(registros, argv[1], registrosPorCidade);
                    ord->quicksortPre(registros, 0, qtdRegistros);
                    totalDiario(registros, qtdRegistros, registrosPorCidade);
                    geraCSV(registros, 100, "teste-pre-processamento.csv");

                }
                break;
        case 2:
                if(saida==1){
                    Registro * teste = randomReg(registros, 10);
                    imprimeInformacoes(teste,10);
                    delete [] teste;

                }
                else{
                    Registro * teste = randomReg(registros, 100);
                    geraCSV(teste, 100, "teste-importacao.csv");
                    delete [] teste;
                }
                break;
        case 3 :
                if(saida==1){
                    Registro * teste = randomReg(registros, 10);
                    ord->insertsort(teste, 10);
                    imprimeInformacoes(teste,10);
                    delete [] teste;

                }else{
                    Registro * teste = randomReg(registros, 100);
                    ord->insertsort(teste, 100);
                    geraCSV(teste, 100, "teste-insert-sort.csv");
                    delete [] teste;

                }
               break;
        case 4:
                if(saida==1){
                    Registro * teste = randomReg(registros, 10);
                    ord->selectionSort(teste, 10);
                    imprimeInformacoes(teste,10);
                    delete [] teste;

                }else{
                    Registro * teste = randomReg(registros, 100);
                    ord->selectionSort(teste, 100);
                    geraCSV(teste, 100, "teste-selection-sort.csv");
                    delete [] teste;

                }
                break;
        case 5: 
                if(saida==1){
                    Registro * teste = randomReg(registros, 10);
                    ord->quicksort(teste,0, 9);
                    imprimeInformacoes(teste,10);
                    delete [] teste;

                }else{
                    Registro * teste = randomReg(registros, 100);
                    ord->quicksort(teste, 0, 99);
                    geraCSV(teste, 100, "teste-quicksort.csv");
                    delete [] teste;

                }
                break;
        case 6:
                if(saida==1){
                    Registro * teste = randomReg(registros, 10);
                    ord->mergeSort(teste,0, 10);
                    imprimeInformacoes(teste,10);
                    delete [] teste;

                }else{
                    Registro * teste = randomReg(registros, 100);
                    ord->mergeSort(teste,0, 100);
                    geraCSV(teste, 100, "teste-merge-sort.csv");

                    delete [] teste;

                }
                break;
            default: cout << "Opção inválida" << endl;

    }


    //==============TRABALHO==========================//



    //Pré-processamento
    //Registro *registros = new Registro[1500000];
    //Vetor do tipo key value para servir do contador de registros por cidade
    // map<int,int> registrosPorCidade ;
    // Ordena *ord = new Ordena();
    // ofstream outfile(argv[2]);

    // auto start1 = high_resolution_clock::now(); //Inicia contador de tempo

    // int qtdRegistros = processaCsv(registros, argv[1], registrosPorCidade);

    // cout << "leu registros" << endl ;

    // auto stop1 = high_resolution_clock::now(); //Termina de contar o tempo
    // auto duration1 =  duration_cast<milliseconds>(stop1 - start1);

    // outfile << "Tempo de leitura: " << duration1.count() << " ms" << endl;

    // auto start2 = high_resolution_clock::now(); //Inicia contador de tempo

    // ord->quicksortPre(registros, 0, qtdRegistros-1);

    // auto stop2 = high_resolution_clock::now(); //Termina de contar o tempo
    // auto duration2 =  duration_cast<milliseconds>(stop2 - start2);

    // cout <<"ordenou" << endl ;
    // outfile << "Tempo de ordenação pré-processamento " << duration2.count() << " ms" << endl;

    // auto start3 = high_resolution_clock::now(); //Inicia contador de tempo

    // cout<< "calculando o total diario" << endl;
    // totalDiario(registros, qtdRegistros, registrosPorCidade);

    // auto stop3 = high_resolution_clock::now(); //Termina de contar o tempo
    // auto duration3 =  duration_cast<milliseconds>(stop3 - start3);
    // int totalDuration = duration1.count() + duration2.count()+duration3.count();

    // outfile << "Tempo de cálculo de total diário: " << duration3.count() << " ms" << endl;
    // cout << "A operação toda durou " << totalDuration << " milisegundos" << endl;
    // outfile << "Operação toda durou: " << totalDuration << " ms " << endl;
    // outfile.close();

    // //Analise dos algoritmos

    // ofstream saida("saida.txt");

    // int N[5] = {10000, 50000, 100000, 500000, 1000000};
    // Registro *processado = new Registro[1500000];
    // cout << "Lendo arquivo..." << endl;
    // leArquivoProcessado(processado, argv[1]);
    // cout << "Leitura Concluída!" << endl;

    // for (int i = 4; i < 5; i++)
    // {
    //     saida << "Número de registros analisados: " << N[i] << endl;
    //     cout << "Número de registros analisados: " << N[i] << endl;
    //     saida << " " << endl;

    //     for (int k = 3; k < 4; k++)
    //     {
    //         Ordena *ordAnalise = new Ordena();

    //         switch (k)
    //         {
    //         case 0:
    //             saida << "Insertion Sort" << endl;
    //             cout << "Insertion Sort" << endl;
    //             break;
    //         case 1:
    //             saida << "Selection Sort" << endl;
    //             cout << "Selection Sort" << endl;
    //             break;
    //         case 2:
    //             saida << "Merge Sort" << endl;
    //             cout << "Merge Sort" << endl;
    //             break;
    //         case 3:
    //             saida << "Quick Sort" << endl;
    //             cout << "Quick Sort" << endl;
    //             break;
    //         }
    //         int media = 0;

    //         for (int m = 0; m < 5; m++)
    //         {
    //             Registro *analise = randomReg(processado, N[i]);
    //             saida << "M = " << m << endl;
    //             cout << "M = " << m << endl;
    //             auto analiseStart = high_resolution_clock::now(); //Inicia contador de tempo
    //             switch (k)
    //             {
    //             case 0:
    //                 ordAnalise->insertsort(analise, N[i]);
    //                 break;
    //             case 1:
    //                 ordAnalise->selectionSort(analise, N[i]);
    //                 break;
    //             case 2:
    //                 ordAnalise->mergeSort(analise, 0, N[i]);
    //                 break;
    //             case 3:
    //                 ordAnalise->quicksort(analise, 0, N[i]);
    //                 break;
    //             }
    //             auto analiseStop = high_resolution_clock::now(); //Inicia contador de tempo
    //             auto analiseDuration = duration_cast<milliseconds>(analiseStop - analiseStart);
    //             media += analiseDuration.count();

    //             saida << "Número de comparações: " << ordAnalise->getNumComparacao() << endl;
    //             saida << "Número de trocas: " << ordAnalise->getNumTroca() << endl;
    //             saida << "Tempo de execução: " << analiseDuration.count() << " ms" << endl;
    //             saida << " " << endl;

    //             delete[] analise;
    //         }
    //         saida << "Media dos tempos de execução: " << media / 5 << " ms" << endl;
    //         saida << " " << endl;

    //         // delete[] ordAnalise;
    //     }
    //     saida << " ================================= " << endl;
    // }

    // saida.close();

    delete[] registros;
    //delete[] processado;
    system("pause");
    return 0;
};
