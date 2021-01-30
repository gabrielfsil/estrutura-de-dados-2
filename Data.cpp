#include "Data.h"
#include "stdlib.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

Data::Data()
{
}

void split(string data, int vet[])
{

    
    vet[0] = std::stoi(data.substr(0, '-'));
    vet[1] = std::stoi(data.substr(5, '-'));
    vet[2] = std::stoi(data.substr(8));
    
}

Data::Data(string data)
{

    int arrayDate[3];

    split(data, arrayDate);

    Data::ano = arrayDate[0];
    Data::mes = arrayDate[1];
    Data::dia = arrayDate[2];
    
}

Data::Data(int dia, int mes, int ano)
{

    Data::dia = dia;
    Data::mes = mes;
    Data::ano = ano;
}

Data::~Data()
{
}

void Data::setDia(int dia)
{

    Data::dia = dia;
}

void Data::setMes(int mes)
{

    Data::mes = mes;
}

void Data::setAno(int ano)
{

    Data::ano = ano;
}

int Data::getDia()
{

    return Data::dia;
}

int Data::getMes()
{

    return Data::mes;
}

int Data::getAno()
{

    return Data::ano;
}

void Data::imprimir()
{

    cout << dia << "/" << mes << "/" << ano;
}

//Função que compara duas datas
// retorna -1 se a data que invoca a função for menor que o parâmetro
// retorna 1 se a data que invoca a função for maior que o parâmetro
// retorna 0 se a as datas forem iguais
int Data::compareTo(Data data){

    int dia1 = this->getDia();
    int dia2 = data.getDia();
    int mes1 = this->getMes();
    int mes2 = data.getMes();
    int ano1 = this->getAno();
    int ano2 = data.getAno();

    if(ano1 > ano2){
        return 1;
    }else if (ano1 == ano2){
        if(mes1>mes2){
            return 1;
        }else if(mes1 == mes2){
            if(dia1>dia2){
                return 1;
            }else if (dia1 == dia2){
                return 0;
            }else{
                return -1;
            }
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}