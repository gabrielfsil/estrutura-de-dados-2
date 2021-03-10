#include "Registro.h"
#include <string>
#include <stdlib.h>

using namespace std;

Registro::Registro(){

};

Registro::~Registro(){

    // delete Registro::data;
};

int Registro::getCodEstado()
{
    return this->codEstado;
}


void Registro::setCodEstado(int codEstado)
{
    this->codEstado = codEstado;
}


int Registro::getCodCidade()
{
    return this->codCidade;
}


void Registro::setCodCidade(int codCidade)
{
    this->codCidade = codCidade;
}


string Registro::getNomeCidade()
{
    return this->nomeCidade;
}


void Registro::setNomeCidade(string nomeCidade)
{
    this->nomeCidade = nomeCidade;
}


float Registro::getLat()
{
    return this->lat;
}


void Registro::setLat(float lat)
{
    this->lat = lat;
}


float Registro::getLon()
{
    return this->lon;
}


void Registro::setLon(float lon)
{
    this->lon = lon;
}


string Registro::getCapital()
{
    return this->capital;
}


void Registro::setCapital(string capital)
{
    this->capital = capital;
}