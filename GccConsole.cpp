// GccConsole.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
int AngleDefault = 0;


int speedPin_M1 = 5;     //M1 Gauche
int speedPin_M2 = 6;     //M2 Droite
int directionPin_M1 = 4;     //M1 Direction Control
int directionPin_M2 = 7;     //M1 Direction Control

int main()
{
	std::string msg = getMsg();

	int pos1 = msg.find("a");
	int pos2 = msg.find("b");
	int pos3 = msg.find("c");
	int pos4 = msg.find("d");

	std::string Accelerometre = msg.substr(0+1, pos2-pos1-1);

	std::cout << "Accelerometre : " << Accelerometre << std::endl;

	std::string TensionIndex = msg.substr(pos2+1,pos3-pos2-1);

	std::cout << "Tension : " << TensionIndex << std::endl;

	std::string TensionPouce = msg.substr(pos3 + 1, pos4 - pos3 - 1);

	std::cout << "TensionPouce : "<< TensionPouce<<std::endl;

	//float vitesse = stof(TensionIndex);

	//vitesse = vitesse + 0.1;

	//std::cout << vitesse << std::endl;
	int AngleMesure = ControleAngle(stoi(Accelerometre));
	if (! AngleDefault == AngleMesure + 5 || ! AngleDefault == AngleMesure - 5)
	{
		AngleDefault = AngleMesure;
	}

	ControleMoteur(AngleDefault, stoi(TensionPouce), stof(TensionIndex));

	//stdd::cout <<"Angle attendu : "<< ControleAngle(stoi(Accelerometre)) << std::endl;




	system("PAUSE");

    return 0;
}


std::string getMsg()
{
	return "a500b3.15c1d";

}


int ControleAngle(int TensionAngle)
{

	if ((TensionAngle >= 0) && (TensionAngle <= 128))
	{
		return -90;
	}
	else if ((TensionAngle >= 128) && (TensionAngle <= 256))
	{
		return -70;
	}
	else if ((TensionAngle >=256) && (TensionAngle <= 384))
	{
		return -50;
	}
	else if ((TensionAngle >= 384) && (TensionAngle <= 500))
	{
		return -25;
	}
	else if ((TensionAngle >= 500) && (TensionAngle <= 550))
	{
		return 0;
	}
	else if ((TensionAngle >= 550) && (TensionAngle <= 678))
	{
		return 25;
	}
	else if ((TensionAngle >= 678) && (TensionAngle <= 806))
	{
		return 50;
	}
	else if ((TensionAngle >= 806) && (TensionAngle <= 934))
	{
		return 70;
	}
	else if (TensionAngle > 934);
	{
		return 90;
	}
}
int LOW = 0;
int HIGH = 0;
void ControleMoteur(int Angle, int Sens, float Tension)
{
	
	float vitesseFloat = (Tension * 85) - 25.5;
	if (vitesseFloat < 0)
	{
		vitesseFloat = 0;
	}

	int VitessePWM = vitesseFloat;
	if (VitessePWM < Angle)
	{
		if (Angle < 0)
		{
			analogWrite(speedPin_M2, VitessePWM+Angle);
			digitalWrite(directionPin_M1, LOW);
			analogWrite(speedPin_M1, VitessePWM);    // On tourne a gauche, donc on supprime l'angle a la vitesse
			digitalWrite(directionPin_M2, LOW);
		}
		if (Angle > 0)
		{
			analogWrite(speedPin_M2, VitessePWM ); // On tourne a droite, donc on supprime l'angle a la vitesse
			digitalWrite(directionPin_M1, LOW);
			analogWrite(speedPin_M1, VitessePWM+Angle);
			digitalWrite(directionPin_M2, LOW);
		}
	}
		else if (Sens == 1)
		{
			if (Angle < 0)
			{
				analogWrite(speedPin_M2, VitessePWM);
				digitalWrite(directionPin_M1, LOW);
				analogWrite(speedPin_M1, VitessePWM-Angle);    // On tourne a gauche, donc on supprime l'angle a la vitesse
				digitalWrite(directionPin_M2, LOW);
			}
			if (Angle > 0)
			{
				analogWrite(speedPin_M2, VitessePWM - Angle); // On tourne a droite, donc on supprime l'angle a la vitesse
				digitalWrite(directionPin_M1, LOW);
				analogWrite(speedPin_M1, VitessePWM);   
				digitalWrite(directionPin_M2, LOW);
			}
			else
			{
				analogWrite(speedPin_M2, VitessePWM ); // Tout droit tchou tchou
				digitalWrite(directionPin_M1, LOW);
				analogWrite(speedPin_M1, VitessePWM);
				digitalWrite(directionPin_M2, LOW);
			}
		}
		else if (Sens == 0)
		{
			if (Angle < 0)
			{
				analogWrite(speedPin_M2, VitessePWM);
				digitalWrite(directionPin_M1, HIGH);
				analogWrite(speedPin_M1, VitessePWM - Angle);    // On tourne a gauche, donc on supprime l'angle a la vitesse
				digitalWrite(directionPin_M2, HIGH);
			}
			if (Angle > 0)
			{
				analogWrite(speedPin_M2, VitessePWM - Angle); // On tourne a droite, donc on supprime l'angle a la vitesse
				digitalWrite(directionPin_M1, HIGH);
				analogWrite(speedPin_M1, VitessePWM);
				digitalWrite(directionPin_M2, HIGH);
			}
			else
			{
				analogWrite(speedPin_M2, VitessePWM); // Tout droit tchou tchou
				digitalWrite(directionPin_M1, HIGH);
				analogWrite(speedPin_M1, VitessePWM);
				digitalWrite(directionPin_M2, HIGH);
			}
		}

}

void digitalWrite(int inutile,int inutilebis){}
void analogWrite(int inutilebis,  int inutile){}

