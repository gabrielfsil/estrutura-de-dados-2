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
    cout<< "CSV GERADO saida.scv" << endl;
    cout << "\n***" << endl;

}

void geraCSV(Registro *registros, int N)
{
    ofstream arq("saida.csv");

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
void embaralhaObj(Registro *registro, int tamanho, int k)
{
    srand(time(NULL) * k);
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
void leArquivoCsv(Registro *registros, int N, string fileDirectory)
{
    ifstream myfile(fileDirectory);
    string line;
    vector<string> dados;

    if(myfile.is_open())
    {

        for(int i=0; i<N+1; i++)
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
        }

        embaralhaObj(registros, N , 3);
        
        myfile.close();      
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
}

void totalDiario(Registro *registros, int N)
{

    for(int i = N-1 ; i >= 0; i--)
    {
        int j = i-1;
        while((registros[i].getCidade() != registros[j].getCidade()) && j>=0)
            j--;        
        if(j>=0)
            registros[i].setCasos(registros[i].getCasos() - registros[j].getCasos());   
    }

}


int main(int argc, char *argv[]){

    int N;
    cout << "Digite o numero de registros que deseja analisar" << endl;
    cin >> N;

    Registro *registros = new Registro[N];
    Ordena *ord = new Ordena();

    leArquivoCsv(registros, N, argv[1]);
    //imprimeInformacoes(registros,N);
    ord->selectionSortPre(registros, N);  
    totalDiario(registros, N);
    //ord->selectionSort(registros, N);
    ord->mergeSort(registros,0,N);
    geraCSV(registros, N);
    system ("pause");

    delete[] registros;
    
    return 0;
};
