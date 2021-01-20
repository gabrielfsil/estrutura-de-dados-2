#ifndef DATA_H
#define DATA_H
#include <string>
#include <stdlib.h>

using namespace std;

class Data{

    public:
        Data();
        Data(string data);
        Data(int dia, int mes, int ano);
        ~Data();
        void setDia(int dia);
        void setMes(int mes);
        void setAno(int ano);
        int getDia();
        int getMes();
        int getAno();
        void imprimir();

    private:
        int dia;
        int mes;
        int ano;
};

#endif // DATA_H