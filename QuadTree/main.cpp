#include <iostream>
#include <fstream>
#include <cstdlib>
#include <bits/stdc++.h>
#include <stdlib.h>


#include "QuadTree.h"

using namespace std;

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

    //state_code,city_code,city_name,lat,long,capital
    // 52,5200050,Abadia de Goiás,-16.7573,-49.4412,FALSE
    // array[0] = "52"
    // array[1] = "5200050"
    // array[2] = "Abadia de Goiás"
    // array[3] = "-16.757"
    // array[4] = "-49.4412"
    // array[5] = "FALSE"

    return;
}

int leArquivo(QuadTree * arvore, string fileDirectory)
{
    ifstream myfile(fileDirectory);
    string line;
    vector<string> dados;
    int i = 0;

    if (myfile.is_open())
    {
        cout << "Inserido registros na árvore... " <<endl;

        while (!myfile.eof())
        {
            getline(myfile, line);
            //Pula a primeira linha
            if (i != 0)
            {
                //Cria um novo registro e um novo nós
                 Registro * registro = new Registro();
                //  NoArv * p = new NoArv();

                //Divide as informações da linha em vetores de string
                //esses são os dados que constituirão o registro
                split(line, ',', dados);
                
                registro->setCodEstado(stoi(dados[0]));
                registro->setCodCidade(stoi(dados[1]));
                registro->setNomeCidade(dados[2]);
                registro->setLat(stof(dados[3]));
                registro->setLon(stof(dados[4]));
                registro->setCapital(dados[5]);
                            
                //Limpa o vetor dos dados da linha para reuso
                dados.clear();


                //Insere o registro na árvore
                arvore->insere(registro);

            }
            i++;
        }
        return i - 1;

        myfile.close();
    }
    else
        cerr << "ERRO: O arquivo nao pode ser aberto!" << endl;
    return 0;
}

int main(int argc, char *argv[])
{

    QuadTree * arv = new QuadTree();

    cout << "Lendo arquivo..." << endl;
    leArquivo(arv, argv[1]);

    cout << endl;

   // cout << "Imprimindo arvore" << endl;

    //cout << endl;

   // arv->imprime();

    cout << endl;

    cout << "Buscando cidades na faixa (-1.2, -50.0) - (-0.9, -30.0) " << endl;
    //-2.0, -0.0, - 0.7, -50.0
    //-30.0, -51.0, -10.0, -30.0

    vector <Registro*> cidades = arv->buscaRange(-1.2, -50.0, - 0.9, -30.0);
   // cout << "De volta a main" << endl;

   // cout  << cidades.size() << endl;

    //cout << "erro ao tirar o size?" << endl;
    if(cidades.size() == 0)
        cout << "Não há cidades presentes nessa faixa" << endl;
    else
        for(int i = 0; i < cidades.size(); i++)
        {
            cout << "[" << cidades[i]->getCodCidade() << "] "<< cidades[i]->getNomeCidade() <<
            "[" << cidades[i]->getLat() << " , " << cidades[i] -> getLon() << "]"<< endl;
        }


    // cout << "Busca a cidade Abadia de Goias: " << arv->busca(-16.7573,-49.4412) << endl;
    // cout << "Busca a cidade Abaetuba: " << arv->busca(-1.72183,-48.8788) << endl;
    // cout << "Busca a cidade Juiz de Fora: " << arv->busca(-21.7595,-43.3398) << endl;
    // cout << "Busca a cidade Santo Antonio do Paraiso: " << arv->busca(-23.4969,-50.6455) << endl;
    // cout << "Busca a cidade Irineopolis: " << arv->busca(-26.242,-50.7957) << endl;
    // cout << "Busca a cidade Nova Yorwk: " << arv->busca(-2.92887 ,-44.9357) << endl;






    

    system ("pause");
    return 0;
}

