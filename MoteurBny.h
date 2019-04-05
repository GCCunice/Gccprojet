#ifndef _MOTEURBNY_H
#define _MOTEURBNY_H


#include "Cherokey.h"
#include "RadarRecul.h"

class Ultrason;

class MoteurBny {
  private:
    Ultrason * ;

    Cherokey ;

    RadarRecul ;


  public:
    bool getObstacleAvant(bool presenceAvant);

    bool getObstacleArriere(const  & presenceArriere);

     deplacement(int MDA, int MGA, int MDARr, int MGARr,  );

};
#endif
