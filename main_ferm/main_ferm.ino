

#include <tempo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define RELAY1 2
#define HISTERESIS 0.3
#define BUSONEWIRE 9

Tempo t_temp(30*1000); // temporizador para la lectura de temperatura

OneWire oneWire(BUSONEWIRE);
DallasTemperature sensors(&oneWire);
int tempSet;

void setup() {  
  tempSet=16;
  Serial.begin(9600); 
  pinMode(RELAY1,OUTPUT);
digitalWrite(RELAY1,HIGH);
sensors.requestTemperatures();
float temp1=sensors.getTempCByIndex(0); 
Serial.print("OFF  ");
Serial.println(temp1); 

}

void loop() {

  if (t_temp.state()){
        sensors.requestTemperatures();
        float temp1=sensors.getTempCByIndex(0);
        
        if(temp1 > tempSet+HISTERESIS){
          digitalWrite(RELAY1,LOW);
          Serial.print("ON  ");
          Serial.println(temp1);
      }
      else{
        if ( temp1<tempSet-HISTERESIS){ 
          digitalWrite(RELAY1,HIGH); 
          Serial.print("OFF  ");
          Serial.println(temp1);
          }
      }        
  }
}
