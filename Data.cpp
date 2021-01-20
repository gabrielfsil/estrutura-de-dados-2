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