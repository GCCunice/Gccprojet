#include <SPI.h>
#include <LoRa.h>

#define Measure 1
int URECHO = 3;
int URTRIG = 9;
int sensorPin = A0;
int sensorValue = 0;
char msg;
unsigned int DistanceMeasured = 0;
//////////////////
int speedPin_M1 = 5;     //M1 Gauche
int speedPin_M2 = 6;     //M2 Droite
int directionPin_M1 = 4;     //M1 Direction Control
int directionPin_M2 = 7;     //M1 Direction Control

// Paramètre de la réception

int txPower = 14; // from 0 to 20, default is 14
int spreadingFactor = 7; // from 7 to 12, default is 12
long signalBandwidth = 125E3; // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3,41.7E3,62.5E3,125E3,250E3,500e3, default is 125E3
int codingRateDenominator=5; // Numerator is 4, and denominator from 5 to 8, default is 5
int preambleLength=8; // from 2 to 20, default is 8

#define SS 10
#define RST 8
#define DI0 2
#define BAND 875E6 // Here you define the frequency carrier


void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");
  Serial.print("SetFrequency : ");
  Serial.print(BAND);
  Serial.println("Hz");
  Serial.print("SetSpreadingFactor : SF");
  Serial.println(spreadingFactor);
  SPI.begin();
  LoRa.setPins(SS,RST,DI0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
 LoRa.setTxPower(txPower,1);
 LoRa.setSpreadingFactor(spreadingFactor);
 LoRa.setSignalBandwidth(signalBandwidth);
 LoRa.setCodingRate4(codingRateDenominator);
 LoRa.setPreambleLength(preambleLength);
 pinMode(URTRIG, OUTPUT);
  digitalWrite(URTRIG, HIGH);
  pinMode(URECHO, INPUT);
  delay(500);
}

void loop() {
    
  Serial.print(msg);
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while (LoRa.available()) {
      
      msg =(char)LoRa.read();
      //Serial.println(msg);
    }
  }

    if (msg != -1)
    {
 
    putain();
  
     // Serial.println(msg);
      switch (msg)
      {
        case 'z'://Move Forward
          Serial.println("going forward");
          advance (255, 255);  //move forward at max speed
          delay (1000);
          stop();
          break;
        case 's'://Move Backward
          Serial.println("going backward");
          back_off (255, 255);  //move backwards at max speed
          delay (1000);
          stop();
          break;
        case 'q'://Turn Left
          Serial.println("turning left");
          turn_L (255, 255);
          delay (500);
          stop();
          msg= 'x';
          break;
        case 'd'://Turn Right
          Serial.println("turning right");
          turn_R (255, 255);
          delay (500);
          stop();
           msg= 'x';
          break;
        case 'w':
          Serial.println("hello world!");
          break;
        case 'x':
          Serial.println("stopping");
          stop();
          break;
      }
    }
    else stop();
  }
  




void stop(void)
{
  digitalWrite(speedPin_M1, 0);
  digitalWrite(directionPin_M1, LOW);
  digitalWrite(speedPin_M2, 0);
  digitalWrite(directionPin_M2, LOW);
}

//ADVANCE
void advance(char a, char b)
{
  analogWrite (speedPin_M1, a);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M2, b);
  digitalWrite(directionPin_M2, LOW);
}

//MOVE BACKWARDS
void back_off (char a, char b)
{
  analogWrite (speedPin_M1, a);
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M2, b);
  digitalWrite(directionPin_M2, HIGH);
}


//TURN LEFT
void turn_L (char a, char b)
{
  analogWrite (speedPin_M1, a);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M2, b);
  digitalWrite(directionPin_M2, HIGH);
}

//TURN RIGHT
void turn_R (char a, char b)
{
  analogWrite (speedPin_M1, a);
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M2, b);
  digitalWrite(directionPin_M2, LOW);
}

void putain() {
  //Serial.print("Distance Measured = ");
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  if(Measure) {
    unsigned long LowLevelTime = pulseIn(URECHO, LOW);
    if(LowLevelTime >= 45000){
   //   Serial.print("Invalid");
    }
    else{
      DistanceMeasured = LowLevelTime /50;
     Serial.print(DistanceMeasured);
     Serial.println("cm");
    }
  }
  /*
  else{
    sensorValue = analogRead(sensorPin);
    if(sensorValue <= 10){
     // Serial.print("Invalid");
    }
   else{
      sensorValue = sensorValue*0.718;
      Serial.print(sensorValue);
     Serial.println("cm");
    }
  }*/
  if(DistanceMeasured<30){
   // Serial.println("AAAAAAAAAAAAAAAAAAAAAAAAAAA");
    msg = 'x';      //ICI se trouve la valeur de retour*/
 }
}
