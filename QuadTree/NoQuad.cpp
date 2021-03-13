#include "NoQuad.h"
#include "Cidade.h"
#include <string>
#include <stdlib.h>

using namespace std;



NoQuad::NoQuad() { 
   NE = NULL;
   NW = NULL;
   SE = NULL;
   SW = NULL;
};

NoQuad::~NoQuad(){ };

void NoQuad::setNE(NoQuad *p) 
{ 
    NE = p; 
}

NoQuad * NoQuad::getNE() 
{ 
    return NE; 
}

void NoQuad::setNW(NoQuad *p) 
{ 
    NW = p; 

}
NoQuad * NoQuad::getNW() 
{ 
    return NW ;
}

void NoQuad::setSE(NoQuad *p) 
{ 
    SE = p; 
}

NoQuad * NoQuad::getSE() 
{ 
    return SE; 
}


void NoQuad::setSW(NoQuad *p) 
{ 
    SW = p; 
}

NoQuad *NoQuad::getSW() 
{ 
    return SW ;
}

void NoQuad::setInfo(Cidade *Cidade) 
{ 
    info = Cidade; 
}
Cidade * NoQuad::getInfo() 
{ 
    return info; 
}

void NoQuad::setX(float val) 
{ 
    X = val;
}

float NoQuad::getX() 
{ 
    return X;
}

void NoQuad::setY(float val) 
{ 
    Y = val;
}

float NoQuad::getY() 
{ 
    return Y;
}

