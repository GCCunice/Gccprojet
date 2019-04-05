#ifndef _CONTROLEMOTEUR_H
#define _CONTROLEMOTEUR_H


#include "Cherokey.h"

class ControleMoteur {
  private:
    Cherokey ;


  public:
    int setConfigMoteur(int tensionFSR1, int & tensionMoteur);

};
#endif
