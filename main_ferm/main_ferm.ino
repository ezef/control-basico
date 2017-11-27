#include <tempo.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define RELAY1 2
#define RELAY2 3

#define HISTERESIS 0.3
#define BUSONEWIRE1 9
#define BUSONEWIRE2 10

Tempo t_temp(30*1000); // temporizador para la lectura de temperatura

OneWire oneWire1(BUSONEWIRE1);
DallasTemperature sensor1(&oneWire1);

OneWire oneWire2(BUSONEWIRE2);
DallasTemperature sensor2(&oneWire2);


int tempSet1;
int tempSet2;
int seguridad1;
int seguridad2;
int parametroseguro;

void setup() {  
tempSet1=16;
tempSet2=16;
seguridad1=0;
seguridad2 = 0;

parametroseguro= 4; 

Serial.begin(9600); 

pinMode(RELAY1,OUTPUT);
digitalWrite(RELAY1,HIGH);

pinMode(RELAY2,OUTPUT);
digitalWrite(RELAY2,HIGH);

sensor1.requestTemperatures();
float temp1=sensor1.getTempCByIndex(0); 

sensor2.requestTemperatures();
float temp2=sensor2.getTempCByIndex(0);

Serial.print("Lectura Sensor 1:  ");
Serial.println(temp1); 

Serial.print("Lectura Sensor 2:  ");
Serial.println(temp2); 

}

void loop() {

  if (t_temp.state()){
	sensor1.requestTemperatures();
	float temp1=sensor1.getTempCByIndex(0);
	
	sensor2.requestTemperatures();
	float temp2=sensor2.getTempCByIndex(0);
	
	if ( seguridad1 < parametroseguro){
		if(temp1 > tempSet1+HISTERESIS){
		  digitalWrite(RELAY1,LOW);
		  Serial.print("Ferm1 ON  ");
		  Serial.print(temp1);
		  seguridad1 = seguridad1 + 1;
		}
		else{
			if ( temp1<tempSet1-HISTERESIS){ 
			  digitalWrite(RELAY1,HIGH); 
			  Serial.print("Ferm1 OFF  ");
			  Serial.print(temp1);		  
			  }
		}
	}else{
	digitalWrite(RELAY1,HIGH); 
	Serial.print("Ferm1 Parada de Emergencia:  ");
	Serial.print(temp1);		
	seguridad1 = 0;
	}	
	
	if ( seguridad2 < parametroseguro){
		if(temp2 > tempSet2+HISTERESIS){
		  digitalWrite(RELAY2,LOW);
		  Serial.print(" Ferm2 ON: ");
		  Serial.println(temp2);
		}
		else{
			if ( temp2<tempSet2-HISTERESIS){ 
			  digitalWrite(RELAY2,HIGH); 
			  Serial.print(" Ferm2 OFF: ");
			  Serial.println(temp2);
			  }
		}
	}else{
	digitalWrite(RELAY2,HIGH); 
	Serial.print("Ferm2 Parada de Emergencia:  ");
	Serial.print(temp2);		
	seguridad2 = 0;
	}	
  }
}
