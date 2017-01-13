//Glue Dispencer Robot

//x,y 2156 steps per inch
//z 1208 steps per inch

#include <AccelStepper.h>


AccelStepper stepperX(1, 8, 9);
AccelStepper stepperY(1, 10, 11);
AccelStepper stepperZ(1, 12, 13);


float stepPerInXY = 2156;
float stepPerInZ = 1208;
int solenoid = 3;
int selectorSwitch = 5;
int glueButton = 6;
int startButton = 7;
float xHome;
float xOff;
float yOff;
float xStep;
float yStep;
float zStep;


void setup() {
  
  stepperX.setMinPulseWidth(200);
  stepperY.setMinPulseWidth(100);
  stepperZ.setMinPulseWidth(200);
  
  stepperX.setMaxSpeed(2800);
  stepperY.setMaxSpeed(2800);
  stepperZ.setMaxSpeed(900);

  stepperX.setAcceleration(5000);
  stepperY.setAcceleration(5000);
  stepperZ.setAcceleration(3000); 

  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);
  stepperZ.setCurrentPosition(0);
  
  pinMode(solenoid, OUTPUT);
  pinMode(selectorSwitch, INPUT_PULLUP);
  pinMode(glueButton, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);

  zStep = .2 * 1208;
  xHome= .5 * 2156 * 4;
  stepperZ.move(zStep);
  stepperZ.runToPosition();
  stepperX.move(-xHome);
  stepperX.runToPosition();

}


void loop() {

  while (digitalRead(startButton) == HIGH) {

    switch(digitalRead(glueButton)) {
      case HIGH:
        digitalWrite(solenoid, HIGH);
        break;
      case LOW:
        digitalWrite(solenoid, LOW);
        break;  
    }
    
  }
  
  switch (digitalRead(selectorSwitch)) {
  case HIGH:
    xOff = 1.5;
    yOff = .85;
    xStep = xOff * 2156 * 4;
    yStep = yOff * 2156 * 4;
    break;
  case LOW:
    xOff = 1.13;
    yOff = .86; 
    xStep = xOff * 2156 * 4;
    yStep = yOff * 2156 * 4;
    break;
    }
  
  stepperX.move(xHome);
  stepperX.runToPosition();
  stepperZ.move(-zStep);
  stepperZ.runToPosition();
  
  digitalWrite(solenoid, HIGH);
  
  stepperX.move(xStep);
  stepperX.runToPosition();
  
  stepperY.move(-yStep);
  stepperY.runToPosition();
  
  stepperX.move(-xStep);
  stepperX.runToPosition();
  
  stepperY.move(yStep);
  stepperY.runToPosition();

  digitalWrite(solenoid, LOW);
  
  stepperZ.move(zStep);
  stepperZ.runToPosition();
 
  stepperX.move(xStep/2);
  stepperX.runToPosition();
  stepperY.move(-yStep/2.5);
  stepperY.runToPosition();

  digitalWrite(solenoid, HIGH);
  stepperZ.move(-zStep);
  stepperZ.runToPosition();
  delay(100);
  digitalWrite(solenoid, LOW);
  
  stepperZ.move(zStep);
  stepperZ.runToPosition();

  stepperX.moveTo(-xHome);
  stepperX.runToPosition();
  stepperY.move(yStep/2.5);
  stepperY.runToPosition();
  
}







