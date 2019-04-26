#include <SPI.h>
#include <LoRa.h>

// Paramètre des moteurs

int AngleDefault = 0;
int speedPin_M1 = 5;     //M1 Gauche
int speedPin_M2 = 6;     //M2 Droite
int directionPin_M1 = 4;     //M1 Direction Control
int directionPin_M2 = 7;     //M1 Direction Control

// Paramètre de la réception

int txPower = 14; // from 0 to 20, default is 14
int spreadingFactor = 9; // from 7 to 12, default is 12
long signalBandwidth = 125E3; // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3,41.7E3,62.5E3,125E3,250E3,500e3, default is 125E3
int codingRateDenominator=5; // Numerator is 4, and denominator from 5 to 8, default is 5
int preambleLength=8; // from 2 to 20, default is 8

#define SS 10
#define RST 8
#define DI0 2
#define BAND 865E6  // Here you define the frequency carrier




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


/*String getMsg()
{ 
  while(LoRa.parsePacket() != 0)
  {  
  }
    return ((char)LoRa.read());
}*/
  
void setup() 
{
 Serial.begin(115200);
 SPI.begin();
}

void loop() 
{
  String msg="a0b0c0d0";
  //String msg = getMsg();
  //Serial.println(msg);
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      //Serial.println((char)LoRa.read());
      
      while( ! LoRa.read()=='d')
      {
      msg = msg + LoRa.read();
      Serial.println(msg);
      }
      //msg = (char)LoRa.read();
      //Serial.print(msg);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
  // String msg = "a129b2.15c1d";
  int pos1 = msg.indexOf("a");
  int pos2 = msg.indexOf("b");
  int pos3 = msg.indexOf("c");
  int pos4 = msg.indexOf("d");
  String Accelerometre = msg.substring(0+1, pos2);
  //Serial.println(Accelerometre);
  String TensionIndex = msg.substring(pos2+1,pos3);
  //Serial.println(TensionIndex);
  String TensionPouce = msg.substring(pos3 + 1, pos4);
  //Serial.println(Accelerometre.toInt());
  int AngleMesure = ControleAngle(Accelerometre.toInt());
  AngleDefault = AngleMesure;
  //Serial.println(AngleMesure);
  ControleMoteur(AngleDefault, TensionPouce.toInt(), TensionIndex.toFloat());
}


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
