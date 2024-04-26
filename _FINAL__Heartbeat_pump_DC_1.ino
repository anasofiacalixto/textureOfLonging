//// Code by Ana Sofia Calixto based on the open source code Example5_HeartRate using the Spaarkfun MAX30105 Library, by Nathan Seidle @ SparkFun Electronics (2016)
//// https://github.com/sparkfun/MAX30105_Breakout 
//// This code is used to move a DC Motor based on the data received from a MAX30105 sensor measuring the average heartbeat

// Hardware Connections:
//  -5V = 5V (3.3V is allowed)
//  -GND = GND
//  -SDA = A4 (or SDA)
//  -SCL = A5 (or SCL)
//  -INT = Not connected

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

// initialize the MAX30105 sensor object
MAX30105 particleSensor;

// constants for the calculation of the input
const byte RATE_SIZE = 4; // increase for more averaging
byte rates[RATE_SIZE];     // array of heart rates
byte rateSpot = 0;
long lastBeat = 0; // time at which the last beat occurred

// variables for heart rate and motor control
float beatsPerMinute;
int beatAvg;
int prevBeatAvg = 0; // variable to store the previous beatAvg value

// Motor A connections
int enA = 3;
int in1 = 4;
int in2 = 5;

void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) // use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place finger on the sensor with steady pressure.");

  particleSensor.setup(); // configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); // turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0);   // turn off Green LED

  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // turn off motor - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void loop()
{
  
  // read the infrared (getIR) value from the sensor
  long irValue = particleSensor.getIR();
  
  // check for a heartbeat
  if (checkForBeat(irValue) == true)
  {
    // we sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    // calculate beats per minute (BPM)
    beatsPerMinute = 60 / (delta / 1000.0);

    // if BPM is within this range (not too slow, not to high):
    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      // get the data gotten from the sensor, then get ready to get the next data
      // rates is a book where data is stored
      // rateSpot++ is turning the page for the next information to be written
      // (byte)beatsPerMinute is the number of beats sensed, to be written down
      rates[rateSpot++] = (byte)beatsPerMinute; // store this reading in the array
    
      // after getting all the data, go back and start over 
      // rateSpot keeps track on which page we are
      // RATE_SIZE is the total of pages in the book
      rateSpot %= RATE_SIZE;                    // wrap variable

      // take average of readings
      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;

      // if beatAvg changes, trigger motor movement
      if (beatAvg != prevBeatAvg)
      {
        speedControl(); // adjust motor speed based on heart rate
        prevBeatAvg = beatAvg; // update previous beatAvg value
      }
    }
  }

  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);

  // check if the finger is correctly placed
  if (irValue < 50000)
    Serial.print(" No finger?");

  Serial.println();
}

// control speed of the motors
void speedControl()
{
  // turn on motors - REVERSED
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // set motor speed based on the current beatAvg value
  int motorSpeed = map(beatAvg, 20, 255, 0, 255);
  analogWrite(enA, 255);

  // delay to allow one full spin
  delay(1000);

  // turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  // delay before the motor can spin again
  delay(1000);
}
