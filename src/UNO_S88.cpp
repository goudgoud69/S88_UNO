#include "UNO_S88.h"
#include <Arduino.h>

const byte clockS88 = 2;      // clock S88 pin = 2
int clockCounter=0;           // 16 tops
const byte PSS88 = 3;         // PS S88 pin = 3
long loopCounter=0;           //for reset from ECOS
const byte dataIn=0;          //data input from next Arduino in S88 chain pin = 0
const byte dataOut=1;         //data output pin=1
unsigned int sensors=0;       // sensor 8/16 bits
unsigned int data=0xffff;     // buffer
int nbsensors;                // nb sensors 8 or 16
int beginPin = 4;             // first pin
int endPin8 = 12;             // last pin for 8 sensors
int endPin16 = 21;            // last pin for 16 sensors
int endPin;

const byte debug = true;

void PS() {
    clockCounter=0;
    data=sensors;
    sensors=0;
    loopCounter++;
}

void clock() {
    digitalWrite(dataOut,bitRead(data,clockCounter)); // shift to next
    delayMicroseconds(16);
    bitWrite(data,clockCounter,digitalRead(dataIn)); // shift from previous
    clockCounter =(clockCounter +1) % nbsensors;     // modulo nb sensors
}

void S88_Setup(int nb_sensors) {
    nbsensors = nb_sensors;
    if (nbsensors == 8) {endPin = endPin8;} else {endPin = endPin16;}
    pinMode(clockS88, INPUT_PULLUP);
    attachInterrupt(0,clock,RISING);    //pin 2 = clock interrupt 0
    pinMode(PSS88, INPUT_PULLUP);
    attachInterrupt(1,PS,RISING);       //pin 3 = PS interrupt 1
    pinMode(dataIn,INPUT_PULLUP);       //pin 0 = data in from next Arduino S88 in chain
    pinMode(dataOut, OUTPUT);           //pin 1 = data out to ECoS or to previous Arduino in S88 chain
    for (int i = beginPin; i< endPin;i++) {
      pinMode(i,INPUT_PULLUP);

      if (debug) Serial.begin(115200); 
         
   }  // init sensors
}

void S88_Loop() {
    if (debug) {
      Serial.print("loopCounter : ");
      Serial.print(loopCounter);
      Serial.print("\t");
    }
    if (loopCounter==20){bitSet(sensors,0);}  // reset management
    for (int i = 4; i<endPin;i++) {
      int reading = digitalRead(i);
      if (debug) Serial.print(reading);
      if (!reading) {bitSet(sensors,i-4);} // update sensors
    }
      
    if (debug) {
      Serial.print(" ");
      Serial.print(sensors);
      Serial.print("\n");
    }
}
