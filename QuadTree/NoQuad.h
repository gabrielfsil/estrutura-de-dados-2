#ifndef NoQuad_H
#define NoQuad_H
#include "Registro.h"


class NoQuad
{
  public:
    NoQuad();
    ~NoQuad();
    void setNE(NoQuad *p);
    NoQuad * getNE();
    void setNW(NoQuad *p);
    NoQuad * getNW();
    void setSE(NoQuad *p);
    NoQuad * getSE();
    void setSW(NoQuad *p);
    NoQuad * getSW();
    void setInfo(Registro *registro);
    Registro * getInfo();
    void setX(float X);
    float getX();
    void setY(float Y);
    float getY();



   
  private:
    NoQuad* NE; // nó nordeste
    NoQuad* NW; // nó sudodeste
    NoQuad* SE; // nó sudeste
    NoQuad* SW; // nó sudoeste
    Registro * info;  // informacao do nó
    float X;
    float Y;
};

#endif // NoQuad_H_INCLUDED
