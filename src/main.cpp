#include <Arduino.h>

#include "UNO_S88.h"    // la librairie S88 pour les UNO/Nano

/*
 * Résumé
 * 
 * int nbsensors;                // nb sensors 8 or 16
 * int beginPin = 4;             // first pin
 * int endPin8 = 12;             // last pin for 8 sensors
 * int endPin16 = 21;            // last pin for 16 sensors
 * 
 * pin 2 = clock interrupt 
 * pin 3 = PS interrupt 1
 * pin 0 = data in from next Arduino S88 in chain
 * pin 1 = data out to ECoS or to previous Arduino in S88 chain
 * 
 * 
 */
     
void setup() {
  //Serial.begin(115200);
  S88_Setup(8);        // on donne le nombre capteur 8 ou 16
}
     
void loop() {
  S88_Loop();           // boucle sur les capteurs
}