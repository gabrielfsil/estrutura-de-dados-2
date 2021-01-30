#include "Registro.h"
#include "Data.h"
#include <string>
#include <stdlib.h>

using namespace std;

Registro::Registro(){

};

Registro::Registro(string data, string sigla, string cidade, int codigo, int casos, int mortes){

    
    Registro::data = Data(data);
    Registro::sigla = sigla;
    Registro::cidade = cidade;
    Registro::casos = casos;
    Registro::mortes = mortes; 
    Registro::codigo = codigo;
    Registro::dataStr = data;

};

Registro::~Registro(){

    // delete Registro::data;
};

void Registro::setData(string str){
    Data date = Data(str);
    Registro::data = date;
    Registro::dataStr = str;

}

void Registro::setSigla(string sigla){

    Registro::sigla = sigla;
}

void Registro::setCidade(string cidade){

    Registro::cidade = cidade;
}

void Registro::setCasos(int casos){

    Registro::casos = casos;
}

void Registro::setMortes(int mortes){

    Registro::mortes = mortes;
}

void Registro::setCodigo(int codigo){

    Registro::codigo = codigo;
}

string Registro::getSigla(){
    return Registro::sigla;
}

string Registro::getCidade(){
    return Registro::cidade;
}

int Registro::getCasos(){
    return Registro::casos;
}

int Registro::getMortes(){
    return Registro::mortes;
}

int Registro::getCodigo(){
    return Registro::codigo;
}


Data Registro::getData(){
    return Registro::data;
}

string Registro::getDataStr(){
    return Registro::dataStr;
}