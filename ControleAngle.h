#ifndef _CONTROLEANGLE_H
#define _CONTROLEANGLE_H


#include "Cherokey.h"

class ControleCervoBny;

//Angle defini selon mAccel ( l'argument )
//If mAccel>0
//	AngleMDA=mAccel
//If mAccel<0
//	AngleMGA=mAccel
//Range a définir ( 0 - 10 = 0 / 10-20=15 ) Valeur Absolu
class ControleAngle {
  private:
    Cherokey ;


  public:
    int setConfigAngle(int acceleration, int & differenceVitesse);


  private:
    ControleCervoBny * ;

};
#endif
