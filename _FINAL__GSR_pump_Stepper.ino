//// Code by Ana Sofia Calixto based on the open source code ConstantSpeed under the AccelStepper library, copyright (C) 2009 Mike McCauley
//// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $
//// This code is used to move a Stepper Motor based on the data received from a GSR sensor

#include <AccelStepper.h>

const int analogInPin = A0;
const int analogOutPin = 9;

int sensorValue = 0;
int outputValue = 0;

long receivedMMdistance = 0; // number of steps
long receivedDelay = 0; // steps per second

// Variaable to later determine if motor is allowed to run or not 
bool runallowed = false;  

AccelStepper stepper(1, 8, 9);

void setup() {
  Serial.begin(9600);
  Serial.println("Testing motor");
  stepper.setMaxSpeed(2000); // maximum speed of the Stepper Motor to avoid overheating 
  stepper.setAcceleration(1000); // how quickly the motor changes its speed 
  stepper.disableOutputs(); // turns off motor when not in use to avoid overheating
}

void loop() {
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 742, 405, 0, 255);
  analogWrite(analogOutPin, outputValue);

  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

  delay(100);

  if (outputValue >= 0 && outputValue < 15) {
    runallowed = true;
    receivedMMdistance = 20; // number of steps for the motor to move
    receivedDelay = 1000; // delay to specify the speed of the motor
    Serial.println("Moving the motor...");
    stepper.enableOutputs(); // enables data to be sent to the driver, and the motor to receive power
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  } 

  else
    if (outputValue >= 16 && outputValue < 30) {
    runallowed = true;
    receivedMMdistance = 300;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);

  }

    else
    if (outputValue >= 31 && outputValue < 45) {
    runallowed = true;
    receivedMMdistance = 4000;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 46 && outputValue < 60) {
    runallowed = true;
    receivedMMdistance = 500;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 61 && outputValue < 75) {
    runallowed = true;
    receivedMMdistance = 6000;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

  
    else
    if (outputValue >= 76 && outputValue < 90) {
    runallowed = true;
    receivedMMdistance = 7000;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }
    
    else
    if (outputValue >= 91 && outputValue < 105) {
    runallowed = true;
    receivedMMdistance = 800;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 106 && outputValue < 120) {
    runallowed = true;
    receivedMMdistance = 9000;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 121 && outputValue < 135) {
    runallowed = true;
    receivedMMdistance = 100;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 136 && outputValue < 150) {
    runallowed = true;
    receivedMMdistance = 1100;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 151 && outputValue < 165) {
    runallowed = true;
    receivedMMdistance = 12000;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 166 && outputValue < 180) {
    runallowed = true;
    receivedMMdistance = 1300;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 181 && outputValue < 195) {
    runallowed = true;
    receivedMMdistance = 1400;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 196 && outputValue < 205) {
    runallowed = true;
    receivedMMdistance = 15000;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }
  
    else
    if (outputValue >= 206 && outputValue < 220) {
    runallowed = true;
    receivedMMdistance = 160;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 221 && outputValue < 235) {
    runallowed = true;
    receivedMMdistance = 1700;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }

    else
    if (outputValue >= 236 && outputValue <= 255) {
    runallowed = true;
    receivedMMdistance = 180;
    receivedDelay = 1000;
    Serial.println("Moving the motor...");
    stepper.enableOutputs();
    stepper.setMaxSpeed(receivedDelay);
    stepper.move(receivedMMdistance);
  }
  
  else {
    runallowed = false;
    stepper.setCurrentPosition(0);
    Serial.println("STOP ");
    stepper.stop();
    stepper.disableOutputs();
  }

  // set loop for the motor to move as long as there are still steps to run
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
}
