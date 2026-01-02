#include <Arduino.h>
#include "Arduino_LED_Matrix.h"





struct SystemStatus
{
  float temp;
  float maxTemp;
  bool alarmActive;
  unsigned long lastUpdate;
};

SystemStatus mojAlarm = {22.0, 22.0, false, 0};
ArduinoLEDMatrix matrix;

uint8_t rzadgood = 6;
uint8_t kolgood = 6;
uint8_t rzadbad = 4;
uint8_t kolbad = 6;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  mojAlarm.lastUpdate = millis();
 }

 uint8_t frame[8][12] = {0};

 void loop() {
   unsigned long currentMillis = millis();

   if(currentMillis - mojAlarm.lastUpdate >= 1000){
    mojAlarm.lastUpdate = currentMillis;
    mojAlarm.temp = mojAlarm.temp + 0.5;

        if(mojAlarm.maxTemp <= mojAlarm.temp) {
      mojAlarm.maxTemp = mojAlarm.temp;
      Serial.print("maksymalna temperatura układu : ");
      Serial.print(mojAlarm.maxTemp);
      Serial.println();
    }
    
    Serial.print("temp:");
    Serial.print(mojAlarm.temp);
    Serial.print(" |  alarm:");
    Serial.print(mojAlarm.alarmActive);
    Serial.println();
 
   }


    if(mojAlarm.temp > 30) {
    mojAlarm.alarmActive = true;
    } 
          for(int i = 0 ; i < 8; i++) {
        for(int j = 0; j < 12; j++) {
          frame[i][j] = 0;
        }
      }
    
    if(mojAlarm.alarmActive == false) {
      frame[rzadgood][kolgood] = 1;
      frame[rzadgood - 1][kolgood - 1] = 1;
      frame[rzadgood - 2][kolgood - 2] = 1;
      frame[rzadgood - 1][kolgood + 1] = 1;
      frame[rzadgood - 2][kolgood + 2] = 1;
      frame[rzadgood - 3][kolgood + 3] = 1;
      frame[rzadgood - 4][kolgood + 4] = 1;
      frame[rzadgood - 5][kolgood + 5] = 1;
      

    }
      

      else {


      frame[rzadbad][kolbad] = 1;
      frame[rzadbad + 1][kolbad - 1] = 1;
      frame[rzadbad + 2][kolbad - 2] = 1;
      frame[rzadbad - 1][kolbad - 1] = 1;
      frame[rzadbad - 2][kolbad - 2] = 1;
      frame[rzadbad - 1][kolbad + 1] = 1;
      frame[rzadbad - 2][kolbad + 2] = 1;
      frame[rzadbad + 1][kolbad + 1] = 1;
      frame[rzadbad + 2][kolbad + 2] = 1;
      
      
        

      }
      
      matrix.renderBitmap(frame, 8, 12);




  }
    

  