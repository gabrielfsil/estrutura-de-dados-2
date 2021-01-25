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


using namespace std;
using namespace std::chrono;

//Troca o conteudo de duas posições do vetor entre si
void trocaStr(Registro *registros, int index1, int index2)
{
    Registro aux;
    aux = registros[index1];
    registros[index1] = registros[index2];
    registros[index2] = aux;

}

int  totalDiario(Registro *registros, int *casosDia, int N){

    string dataInicial = registros[0].getDataStr();
    casosDia[0] = registros[0].getCasos();
    int dias = 0;

    for(int i =1; i<N; i++){
        // cout << "dia = " << dias << endl;
        // cout << "casos dia: " << casosDia[0] << endl;
        // cout << "data inicial " << dataInicial << " == " << registros[i].getDataStr() << " ? "<< endl;
        if(registros[i].getDataStr() == dataInicial)
        {
            // cout<< "sim, entao" << endl;
            // cout << " casosDia[" <<dias << "]" << " += " << registros[i].getCasos() << endl;
            casosDia[dias] += registros[i].getCasos();
            // cout << "Casos dia [" << dias << "] = " << casosDia[dias] << endl ;
            // cout << "" << endl;

        }else{
            // cout<< "nao, entao" << endl;
            dias++;
            casosDia[dias] = registros[i].getCasos();
            // cout << "dataInicial" << " == " << registros[i].getDataStr() << endl;
            // cout << "dia = " << dias << endl;
            dataInicial = registros[i].getDataStr();
            // cout << "" << endl;
        }
    }
    return dias+1;
}

//Ordenação pelo método de seleção onde a comparação leva 3 critérios, que são data, estado e cidade
void SelectionSorting(Registro *registros, int N){

    string sigla, siglaMin, cidade, cidadeMin;
    int val1, val2;

    for(int i=0; i<N; i++)
    {
        int min = i;

        for(int j = i+1; j<N; j++)
        { 
            if(registros[j].getData().compareTo(registros[min].getData()) == -1)
            {
                            min = j;
            }else if(registros[j].getData().compareTo(registros[min].getData()) == 0)
            {
                sigla= registros[j].getSigla();
                siglaMin = registros[min].getSigla();

                if(sigla < siglaMin)
                {
                    min = j;
                }else if (sigla == siglaMin)
                {
                    cidade = registros[j].getCidade();
                    cidadeMin= registros[min].getCidade();
                    if(cidade < cidadeMin)
                    {
                        min = j;
                    }    
                }
            }
            
        }
        
        trocaStr(registros, min, i);
      
    }

}

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

    arq << "date,state,name,code,cases,deaths" << endl;

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
void leArquivoCsv(Registro *registros, int N)
{
    ifstream myfile("teste.csv");
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

int main(){

    int N = 15;
    Registro *registros = new Registro[N];
    leArquivoCsv(registros, N);
    //imprimeInformacoes(registros,N);
    SelectionSorting(registros, N);

    // int * casosDia = new int [365];
    // int dias = totalDiario(registros, casosDia, N);

    // cout << "Total de casos por dia" << endl;
    // for(int i=0; i < dias; i++)
    // {
    //     cout << "Dia " << i << " :" << casosDia[i] << " casos" << endl;
    // }
    imprimeInformacoes(registros,N);
    geraCSV(registros, N);
    system ("pause");

    delete[] registros;
    
    return 0;
};
