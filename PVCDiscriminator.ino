/* NOTES
 *  to see values from sensor: TOOLS -> SERIAL MONITOR 
 *  Sensor Readings - Control (no bulbs on, box on)
   *  Vis: 258
   *  IR: 252
   *  UV: 0.02
 *  IR Reading (IR bulb on, box on): 63
*/

#include <Wire.h>
#include "Adafruit_SI1145.h"

   // SENSOR
Adafruit_SI1145 uv = Adafruit_SI1145();
// Control values of sensor to be subtracted from read values
int visControl = 258;
int IRControl = 252;
int UVControl = 0.02;

   // LIGHT
const int lightPin =  7;

  // ALERT LED
const int alertLED = 5;

void setup() 
  {
         // LIGHT
      pinMode(lightPin, OUTPUT);
    
        //  SENSOR 
      Serial.begin(9600);
      Serial.println("Adafruit SI1145 test");
      if (! uv.begin()) 
        {
          Serial.println("Didn't find Si1145");
          while (1);
        }
      Serial.println("OK!"); 

      // ALERT LED
      pinMode(alertLED, OUTPUT);
    
  }

void loop()
  {

        //  LIGHT
      digitalWrite(lightPin, HIGH);

      //  ALERT LED
      digitalWrite(alertLED, LOW);

        // SENSOR 
        int Vreading = uv.readVisible();
        int IRreading = uv.readIR();
        int UVreading = uv.readUV();
      Serial.println("===================");
      if (Vreading == 65535)
        Vreading = 0;
      if (IRreading == 65535)
        IRreading = 0;
      if (UVreading == 65535)
        UVreading = 0;
      //Serial.print("Vis: "); Serial.println(Vreading-visControl);
      Serial.print("IR: "); Serial.println(IRreading-IRControl);
      float UVindex = UVreading;
      UVindex /= 100.0;
      //Serial.print("UV: ");  Serial.println(UVindex-UVControl);
    
      delay(500);

        // ALERT LED
      if ((IRreading-IRControl) > 27 && (IRreading-IRControl) < 37 ) // NEED TO CHANGE RANGE FOR PVC ONLY
        {
          digitalWrite(alertLED, HIGH);
          delay(500);
        }
  }
