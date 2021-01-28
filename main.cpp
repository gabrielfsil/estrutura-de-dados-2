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
    for (int i =0; i<N; i++)
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
    cout<< "CSV GERADO " << endl;
    cout << "\n***" << endl;

}

void geraCSV(Registro *registros, int N, string filename)
{
    ofstream arq(filename);

    arq << "Data,Estado,Nome,Codigo,Casos/Dia,Mortes" << endl;

    for(int i = 0; i <N; i++)
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
    while(getline(ss,split, ','))
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


//Função para leitura do arquivo em função da quantidade N de registros desejados
int leArquivoCsv(Registro *registros, string fileDirectory)
{
    ifstream myfile(fileDirectory);
    string line;
    vector<string> dados;
    int i = 0;

    if(myfile.is_open())
    {

        while (!myfile.eof())
        {
            getline(myfile,line);
            //Pula a primeira linha
            if(i!=0)
            {
                //Divide as informações da linha em vetores de string 
                //esses são os dados que constituirão o registro
                split(line, ',', dados);

                registros[i-1].setData(dados[0]);
                registros[i-1].setSigla(dados[1]);
                registros[i-1].setCidade(dados[2]);
                registros[i-1].setCodigo(stoi (dados[3]));
                registros[i-1].setCasos(stoi(dados[4]));
                registros[i-1].setMortes(stoi(dados[5]));

                //Limpa o vetor dos dados da linha para reuso
                dados.clear();
            }
            i++;
        }
        shuffle(registros, i-1);   
        return i-1;   

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

    int *aux = new int [N]();
    Registro *vet = new Registro [N];

    //Uso do srand para variar os números dados na função rand em cada execução
    srand(time(NULL));
    for(int i= 0; i <N; i++)
    {
        int num = rand() % N;
        
        while ((num < 0) || (aux[num]!=0))
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
//O vetor de registros é percorrido de trás para frente e assim que o registro da iteração atual
//encontra o primeiro seguinte a ele, é descontado dos casos do registro atual o valor de casos
//do seu próximo.
void totalDiario(Registro *registros, int N)
{

    for(int i = N-1 ; i > 0; i--)
    {
        int j = i-1;
        while((registros[i].getCidade() != registros[j].getCidade()) && j>0)
            j--;        
        
        if(registros[i].getCidade()==registros[j].getCidade())
            registros[i].setCasos(registros[i].getCasos() - registros[j].getCasos());   
    }

}



int main(int argc, char *argv[]){


    int N;
    cout << "Digite o numero de registros que deseja analisar" << endl;
    cin >> N;

    //Pré-processamento 
    Registro *registros = new Registro[1500000];
    Ordena *ord = new Ordena();

<<<<<<< HEAD
    leArquivoCsv(registros, N, argv[1]);
    //imprimeInformacoes(registros,N);
    ord->selectionSortPre(registros, N);  
    totalDiario(registros, N);
    //ord->selectionSort(registros, N);
    ord->mergeSort(registros,0,N);
    geraCSV(registros, N);
=======
    auto start = high_resolution_clock::now(); //Inicia contador de tempo

    int qtdRegistros = leArquivoCsv(registros, argv[1]);
    ord->selectionSortPre(registros, qtdRegistros);  
    totalDiario(registros, qtdRegistros);

    //Vetor para analise dos algoritmos
    Registro * analise = randomReg(registros, N);

    auto stop = high_resolution_clock::now(); //Termina de contar o tempo
    auto duration =  duration_cast<microseconds>(stop - start);
    cout << "A operação durou " << duration.count() << " milisegundos" << endl;

    // //Modulo de testes
    // int saida;
    // cout << "=====Modulo de testes=====" << endl;
    // cout << "Digite 1 se deseja exibir o resultado no console"<< endl;
    // cout << "Digite 2 se deseja o resultado num arquivo"<< endl;
    // cin >> saida;

    // int opcao;
    // cout << "Escolha uma das opções de teste" << endl;
    // cout << "1 - Pré-Processamento" << endl;
    // cout << "2 - Importacão de N registros aleatórios" << endl;
    // cout << "3 - Ordenação Método Inserção" << endl;
    // cout << "4 - Ordenação Método Seleção" << endl;
    // cout << "5 - Ordenação QuickSort" << endl;
    // cout << "6 - Ordenação MergeSort" << endl;
    // cin >> opcao;



    // switch(opcao)
    // {
    //     case 1 :
    //             if(saida==1){
    //                 Registro * teste = randomReg(registros, 10);
    //                 ord->selectionSortPre(teste, 10);
    //                 imprimeInformacoes(teste,10);
    //             }
    //             else{
    //                 Registro * teste = randomReg(registros, 100);
    //                 ord->selectionSortPre(teste, 100);
    //                 geraCSV(teste, 100, "teste-pre-processamento.csv");

    //             }
    //             break;
    //     case 2:
    //             if(saida==1){
    //                 Registro * teste = randomReg(registros, 10);
    //                 imprimeInformacoes(teste,10);
    //                 delete [] teste;

    //             }
    //             else{
    //                 Registro * teste = randomReg(registros, 100);
    //                 geraCSV(teste, 100, "teste-importacao.csv");
    //                 delete [] teste;
    //             }
    //             break;
    //     case 3 :
    //            //
    //            break;
    //     case 4:
    //             if(saida==1){
    //                 Registro * teste = randomReg(registros, 10);
    //                 ord->selectionSort(teste, 10);
    //                 imprimeInformacoes(teste,10);
    //                 delete [] teste;

    //             }else{  
    //                 Registro * teste = randomReg(registros, 100);
    //                 ord->selectionSort(teste, 100);
    //                 geraCSV(teste, 100, "teste-selection-sort.csv");
    //                 delete [] teste;

    //             }
    //             break;
    //     case 5: //
    //             break;
    //     case 6: 
    //             // if(saida==1){
    //             //     Registro * teste = randomReg(registros, 10);
    //             //     ord->mergeSort(teste,0, 10);
    //             //     imprimeInformacoes(teste,10);
    //             //     delete [] teste;

    //             // }else{  
    //             //     Registro * teste = randomReg(registros, 100);
    //             //     ord->mergeSort(teste,0, 100);
    //             //     imprimeInformacoes(teste,100);
    //             //     delete [] teste;

    //             // }
    //             break;
    //         default: cout << "Opção inválida" << endl;

    // }
    geraCSV(registros, qtdRegistros, "brazil_covid19_cities_processado.csv");

    //geraCSV(analise, N, "saida.csv");
>>>>>>> master
    system ("pause");

    delete[] registros;
    delete[] analise;
    
    return 0;
};
