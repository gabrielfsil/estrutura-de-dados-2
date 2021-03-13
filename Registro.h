#ifndef REGISTRO_H
#define REGISTRO_H
#include <string>
#include "Data.h"
#include <stdlib.h>

using namespace std;

class Registro{

    public:
        Registro();
        Registro(string data, string sigla, string cidade, int casos, int mortes, int codigo);
        ~Registro();
        void setData(string str);
        void setSigla(string sigla);
        void setCidade(string cidade);
        void setCasos(int casos);
        void setMortes(int mortes);
        void setCodigo(int codigo);
        string getSigla();
        string getCidade();
        int getCasos();
        int getMortes();
        int getCodigo();
        Data getData();
        string getDataStr();
        string retornaEmString();


    private:
        Data data;
        string dataStr;
        string sigla;
        string cidade;
        int casos;
        int mortes;
        int codigo;


};

#endif // REGISTRO_H