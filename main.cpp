#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <bits/stdc++.h>
#include <stdlib.h>


using namespace std;
using namespace std::chrono;


//Tipos de dados criados para ser possível a criação de um array de array de strings que guarda
//os dados de cada registro
typedef vector<string> Data;
typedef vector<Data> Register;

// Lê uma linha de registro da tabela e separa os dados das 6 colunas em um array com a quantidade de colunas
//e de acordo com o separador
//O array é de strings
// 
void split(string str, char separator, Data &splits)
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

//Função para leitura do arquivo em função da quantidade N de registros desejados
void leArquivoTextoGeral(int N)
{
    ifstream myfile("brazil_covid19_cities.csv");
    string line;
    Data dados;
    Register registros;

    if(myfile.is_open())
    {
        cout << "Informacoes armazenadas no arquivo:\n\n***" << endl;

        for(int i=0; i<N; i++)
        {
            getline(myfile,line);

            //Pula a primeira linha
            if(i!=0)
            {
                //Divide as informações da linha em vetores de string
                split(line, ',', dados);

                //Adiciona os vetores com informações de cada coluna a uma ocorrência do vetor de registros
                registros.push_back(dados);

                //Limpa o vetor dos dados da linha para reuso
                dados.clear();
            }
        }

        //Percorre os registros salvos e as informações de cada coluna (dado) referente ao mesmo
        for (auto & dados : registros)
        {
            int cont = 0;
            for( auto & dado : dados)
            {
                switch (cont) 
                {
                    case 0 : cout << "Data: ";
                            break;
                    case 1 : cout << "Estado: ";
                            break;
                    case 2 : cout << "Nome: ";
                            break;
                    case 3 : cout << "Codigo: ";
                            break;
                    case 4 : cout << "Casos: ";
                            break;
                    case 5 : cout << "Mortes: ";
                            break;
                }
                cont++;
                cout << dado << endl;

            }
            cout << endl; 
        }
        cout << "\n***" << endl;
        myfile.close();      
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;

}

int main(){

    leArquivoTextoGeral(5);
    system ("pause");
}
