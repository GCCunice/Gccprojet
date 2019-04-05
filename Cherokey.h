#ifndef _CHEROKEY_H
#define _CHEROKEY_H


#include "ControleMoteur.h"
#include "ControleAngle.h"
#include "Ultrason.h"
#include "MoteurBny.h"

class Reception;

class Cherokey {
  private:
    Reception * reception;

     


  public:
     getMsg();

     setConfig();


  private:
    ControleMoteur controleMoteur;			

    ControleAngle controleAngle;

    //Moteur Droit Avant
    
    int MDA;

    //Moteur Gauche Avant
    
    int MGA;

    //Moteur Droit Arriere
    //
    
    int MDARr;

    //Moteur Gauche Arriere
    
    int MGARr;


	int tension;
	
	bool sens;
	
	int angle;
	
	
    Ultrason ;

    MoteurBny ;

};
#endif
