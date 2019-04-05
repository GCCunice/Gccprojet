#ifndef _ULTRASON_H
#define _ULTRASON_H


#include "Cherokey.h"

class MoteurBny;

class Ultrason {
  private:
    Cherokey ;

    MoteurBny * ;


  public:
     doIt();
	 bool getObstacleAvant();

  private:
    //1 Pour presence
    //0 Pas de probleme
    
    bool obstacleAvant;

};
#endif
