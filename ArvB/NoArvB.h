#ifndef NoArvB_H_INCLUDED
#define NoArvB_H_INCLUDED

class NoArvB
{
  public:
    NoArvB(int m, bool folha);//m = ordem
    ~NoArvB();
    int * getChaves();
    void setM(int M);
    int getM();
    void setN(int N);
    int getN();
    void setFolha(bool val);
    bool ehFolha();
    void addChave(int chave);
    void addFilho(NoArvB * filho);
    int getId(int pos);
    void cisao(int j , NoArvB *p);
    NoArvB**  getFilhos();

    
  private:
    int m; //grau minimo
    int * chaves; //m-1 chaves
    NoArvB **filhos;//array de ponteiros para os m filhos
    //filhos[m-2] => filho esquerdo de chaves[m-2] e 
    // filho direito de chaves[m-3]
    //filhos[m-1] é filho direito de chaves [m-2]
    int n; //número de chaves no nó
    bool folha; //indica se o nó é folha ou não
};

#endif // NoArvB_H_INCLUDED
