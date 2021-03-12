#include <iostream>

#include "NoAVL.h"

using namespace std;

NoAVL::NoAVL()               
{ 

}
NoAVL::~NoAVL()              
{ 

}
void NoAVL:: setEsq(NoAVL *p) 
{ 
    esq = p; 
}
void NoAVL:: setInfo(int val) 
{ 
    info = val; 
}
void NoAVL:: setDir(NoAVL *p) 
{ 
    dir = p; 
}
void NoAVL:: setAltura(int k) 
{ 
    altura = k; 
}
void NoAVL:: setFB(int k) 
{ 
    fb = k; 
}

NoAVL* NoAVL::getEsq()       
{ 
    return esq; 
}
int NoAVL::getInfo()         
{ 
    return info; 
}
NoAVL* NoAVL::getDir()       
{ 
    return dir; 
}
int NoAVL::getAltura()         
{
    return altura; 
}

