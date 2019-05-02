/*
 # Edited by:  Matt
 # Date:       2015.09.06
 # Version:    1.1
 # Product:    Cherokey 4WD Mobile Platform
 # SKU:        ROB0102/ROB0117

 # Description:
 # Drive 2 motors with this Cherokey 4WD Mobile Platform
 # Connect D4,D5,D6,D7,GND to UNO digital 4,5,6,7,GND
*/
int counter = 0;
int compte = 0;
#include <SPI.h>
#include <LoRa.h>
// Parameters you can play with :

int txPower = 14; // from 0 to 20, default is 14
int spreadingFactor = 7; // from 7 to 12, default is 12
long signalBandwidth = 125E3; // 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3,41.7E3,62.5E3,125E3,250E3,500e3, default is 125E3
int codingRateDenominator=5; // Numerator is 4, and denominator from 5 to 8, default is 5
int preambleLength=8; // from 2 to 20, default is 8
String payload = "hello"; // you can change the payload

#define SS 10
#define RST 8
#define DI0 2
#define BAND 875E6  // Here you define the frequency carrier

void setup(void) {
    Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
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
// LoRa.setPolarity(1);
 //LoRa.setFSK(); 
  Serial.println("Z avancé , s reculé, d droite, q gauche, x quitter" ) ;
}

void loop() {
  compte =  0;
 
    if (Serial.available()) {
      char val = Serial.read();
    if (val != -1)
    {
      switch (val)
      {
        case 'z'://Move Forward
          //Serial.println("going forward");
          //advance (255, 255);  //move forward at max speed
          while(compte < 10 )
          {
            LoRa.beginPacket();
            Serial.println("z");
            LoRa.print("z");  
            LoRa.endPacket();
            Serial.print(compte);
            counter++;
            compte++;
            delay (10);
            
          }
          
          break;
        case 's'://Move Backward
            while(compte < 10 )
          {
            LoRa.beginPacket();
            Serial.println("s");
            LoRa.print("s");  
            LoRa.endPacket();
            Serial.print(compte);
            counter++;
            compte++;
            delay (10);            
          }
          break;
        case 'q'://Turn Left
             while(compte < 10 )
          {
            LoRa.beginPacket();
            Serial.println("q");
            LoRa.print("q");  
            LoRa.endPacket();
            Serial.print(compte);
            counter++;
            compte++;
            delay (10);            
          }
          break;
        case 'd'://Turn Right
            while(compte < 10 )
          {
            LoRa.beginPacket();
            Serial.println("d");
            LoRa.print("d");  
            LoRa.endPacket();
            Serial.print(compte);
            counter++;
            compte++;
            delay (10);
          }
          break;
        case 'x':
             while(compte < 10 )
          {
            LoRa.beginPacket();
            Serial.println("x");
            LoRa.print("x");  
            LoRa.endPacket();
            Serial.print(compte);
            counter++;
            compte++;
            delay (10);
          }
         
          break;
      }
    }
    
  }
}
