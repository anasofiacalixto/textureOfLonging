//// Code by Ana Sofia Calixto based on the open source code Example8_SPO2 using the Spaarkfun MAX30105 Library, by Nathan Seidle @ SparkFun Electronics (2016)
//// https://github.com/sparkfun/MAX30105_Breakout 
//// This code is used to move a DC Motor based on the data received from a MAX30105 sensor measuring the average SPO2 levels

// Hardware Connections:
//  -5V = 5V (3.3V is allowed)
//  -GND = GND
//  -SDA = A4 (or SDA)
//  -SCL = A5 (or SCL)
//  -INT = Not connected

#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"

MAX30105 particleSensor;

#define MAX_BRIGHTNESS 255

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
uint16_t irBuffer[100]; // infrared LED sensor data
uint16_t redBuffer[100]; // red LED sensor data
#else
uint32_t irBuffer[100]; // infrared LED sensor data
uint32_t redBuffer[100]; // red LED sensor data
#endif

int32_t bufferLength;      // data length
int32_t spo2;              // SPO2 value
int8_t validSPO2;          // indicator to show if the SPO2 calculation is valid
int32_t heartRate;         // heart rate value
int8_t validHeartRate;     // indicator to show if the heart rate calculation is valid

byte pulseLED = 11;  // must be on PWM pin
byte readLED = 13;   // blinks with each data read
 
 // Motor B connections
int enB = 3;
int in3 = 4;
int in4 = 5;

void setup()
{
  Serial.begin(115200);
  pinMode(pulseLED, OUTPUT);
  pinMode(readLED, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // check if the MAX30105 sensor is found
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))
  {
    Serial.println(F("MAX30105 was not found. Please check wiring/power."));
    while (1);
  }

  Serial.println(F("Attach sensor to finger with rubber band. Press any key to start conversion"));
  while (Serial.available() == 0)
    ;
  Serial.read();

  // sensor setup parameters
  byte ledBrightness = 60;
  byte sampleAverage = 4;
  byte ledMode = 2;
  byte sampleRate = 100;
  int pulseWidth = 411;
  int adcRange = 4096;

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
}

void loop()
{
  bufferLength = 100;

  // read data from the sensor and store in buffers
  for (byte i = 0; i < bufferLength; i++)
  {
    while (particleSensor.available() == false)
      particleSensor.check();

    // ask sensor for the red light reding and store it under the red "page"
    redBuffer[i] = particleSensor.getRed();
    // ask sensor for the IR reding and store it under the IR "page"
    irBuffer[i] = particleSensor.getIR();
    // get next sample
    particleSensor.nextSample();

    // print red and IR values
    Serial.print(F("red="));
    Serial.print(redBuffer[i], DEC);
    Serial.print(F(", ir="));
    Serial.println(irBuffer[i], DEC);
  }

  // calculate SPO2 and heart rate using the sensor data
  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

  while (1)
  {
    // shift data in buffers
    for (byte i = 25; i < 100; i++)
    {
      // move the data from pages 26 - 100 to the first 75 pages
      redBuffer[i - 25] = redBuffer[i];
      irBuffer[i - 25] = irBuffer[i];
    }
    
     // read new data from the sensor from pages 76 - 100
    for (byte i = 75; i < 100; i++)
    {
      while (particleSensor.available() == false)
        particleSensor.check();

      digitalWrite(readLED, !digitalRead(readLED));
      // again, ask sensor for the red light reding and store it under the red "page"
      redBuffer[i] = particleSensor.getRed();
      // again, ask sensor for the IR reding and store it under the IR "page"
      irBuffer[i] = particleSensor.getIR();
      // get next sample
      particleSensor.nextSample();

      Serial.print(F("red="));
      Serial.print(redBuffer[i], DEC);
      Serial.print(F(", ir="));
      Serial.print(irBuffer[i], DEC);

      // update SPO2 values
      maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

      Serial.print(F(", HR="));
      Serial.print(heartRate, DEC);

      Serial.print(F(", HRvalid="));
      Serial.print(validHeartRate, DEC);

      Serial.print(F(", SPO2="));
      Serial.print(spo2, DEC);

      Serial.print(F(", SPO2Valid="));
      Serial.println(validSPO2, DEC);
    }

    // after gathering 25 new samples recalculate HR and SP02
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

    // motor control logic
    speedControl();

    Serial.print("IR=");
    Serial.print(irBuffer[99]); // assuming the last value is the most recent
    Serial.print(", SPO2=");
    Serial.println(spo2);

    delay(1000); // add a delay to control the frequency of motor control updates
  }
}

 // motor control function
void speedControl()
{
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // set motor speed based on the current SPO2 value
  int motorSpeed = map(spo2, 70, 100, 0, 255);  
  analogWrite(enB, motorSpeed);

  delay(1000);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(1000);
}
