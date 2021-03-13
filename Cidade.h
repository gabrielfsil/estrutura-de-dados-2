#ifndef Cidade_H
#define Cidade_H
#include <string>
#include <stdlib.h>

using namespace std;

class Cidade{

    public:
        Cidade();
        ~Cidade();
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

#endif // Cidade_H