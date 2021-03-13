#include "Cidade.h"
#include <string>
#include <stdlib.h>

using namespace std;

Cidade::Cidade(){

};

Cidade::~Cidade(){

    // delete Cidade::data;
};

int Cidade::getCodEstado()
{
    return this->codEstado;
}


void Cidade::setCodEstado(int codEstado)
{
    this->codEstado = codEstado;
}


int Cidade::getCodCidade()
{
    return this->codCidade;
}


void Cidade::setCodCidade(int codCidade)
{
    this->codCidade = codCidade;
}


string Cidade::getNomeCidade()
{
    return this->nomeCidade;
}


void Cidade::setNomeCidade(string nomeCidade)
{
    this->nomeCidade = nomeCidade;
}


float Cidade::getLat()
{
    return this->lat;
}


void Cidade::setLat(float lat)
{
    this->lat = lat;
}


float Cidade::getLon()
{
    return this->lon;
}


void Cidade::setLon(float lon)
{
    this->lon = lon;
}


string Cidade::getCapital()
{
    return this->capital;
}


void Cidade::setCapital(string capital)
{
    this->capital = capital;
}