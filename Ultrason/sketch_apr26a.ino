#define Measure 1
int URECHO = 3;
int URTRIG = 5;
int sensorPin = A0;
int sensorValue = 0;

unsigned int DistanceMeasured = 0;

void setup() {
  Serial.begin(9600);
  pinMode(URTRIG, OUTPUT);
  digitalWrite(URTRIG, HIGH);
  pinMode(URECHO, INPUT);
  delay(500);
  Serial.println("Init the sensor");

}

void loop() {
  PWM_Mode();
  delay(100);

}

void PWM_Mode() {
  Serial.print("Distance Measured = ");
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);
  if(Measure) {
    unsigned long LowLevelTime = pulseIn(URECHO, LOW);
    if(LowLevelTime >= 45000){
      Serial.print("Invalid");
    }
    else{
      DistanceMeasured = LowLevelTime /50;
      Serial.print(DistanceMeasured);
      Serial.println("cm");
    }
  }
  else{
    sensorValue = analogRead(sensorPin);
    if(sensorValue <= 10){
      Serial.print("Invalid");
    }
    else{
      sensorValue = sensorValue*0.718;
      Serial.print(sensorValue);
      Serial.println("cm");
    }
  }
}
