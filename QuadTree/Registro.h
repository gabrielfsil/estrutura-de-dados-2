#ifndef REGISTRO_H
#define REGISTRO_H
#include <string>
#include <stdlib.h>

using namespace std;

class Registro{

    public:
        Registro();
        ~Registro();
        void setCodEstado(int codEstado);
        void setCodCidade(int codCidade);
        void setNomeCidade(string nomeCidade);
        void setLat(float lat);
        void setLon(float lon);
        void setCapital(string capital);
        int getCodEstado();
        int getCodCidade();
        string getNomeCidade();
        float getLat();
        float getLon();
        string getCapital();


    private:
        int codEstado;
        int codCidade;
        string nomeCidade;
        float lat;
        float lon;
        string capital;

        
};

#endif // REGISTRO_H