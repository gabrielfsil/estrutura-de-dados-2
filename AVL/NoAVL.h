#ifndef NoAVL_H_INCLUDED
#define NoAVL_H_INCLUDED

class NoAVL
{
  public:
    NoAVL();
    ~NoAVL();          
    void setEsq(NoAVL *p);
    void setInfo(int val);
    void setDir(NoAVL *p);
    void setAltura(int k);
    void setFB(int k);

    NoAVL* getEsq();
    int getInfo();
    NoAVL* getDir();
    int getAltura();
    int getFatorB();
    
  private:
    NoAVL* esq; // ponteiro para o filho a esquerda
    int info;   // informação do No (int)
    NoAVL* dir; // ponteiro para o filho a direita
    int altura; //altura
    int fb; //fator de balanceamento
};

#endif // NoAVL_H_INCLUDED
