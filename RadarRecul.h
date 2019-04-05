#ifndef _RADARRECUL_H
#define _RADARRECUL_H


#include "MoteurBny.h"
#include "buzzerBny.h"

class RadarRecul {
  private:
    MoteurBny ;


  public:
    void doIt();


  private:
    //1 presence
    //0 pas de presence
    
    bool obstacleArriere;

    buzzerBny ;

};
#endif
