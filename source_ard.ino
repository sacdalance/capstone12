// Made by Sir Linnaeus Bundalian
// Modified by Lance Sacdalan

#include <MQ135.h>
#include <Wire.h>
#include <dht.h>

dht DHT;
MQ135 mq135 = MQ135(A0);

#define DHT11_PIN A1

#define RLOAD 22.0
#define RZERO 879.13


void setup(){  
  Serial.begin(9600);
  
}

float convertedMQ135(float mq135Read)
{
  //pull-down resistor value
  int mqR = 22000;
  //rO sensor value
  long rO = 41763;
  //min value for Rs/Ro
  float minRsRo = 0.358;
  //max value for Rs/Ro
  float maxRsRo = 2.428;
  //sensor a coefficient value
  float a = 116.6020682;
  //sensor b coefficient value
  float b = -2.769034857;  


  long rS = ((1024.0 * mqR) / mq135Read) - mqR;
  float rSrO = (float)rS / (float)rO;
  float ppm = a * pow((float)rS / (float)rO, b);

  return ppm;
  
}

void loop(){

    int dhtSensor =  DHT.read11(DHT11_PIN);
    float gr = mq135.getResistance();
    float gc = convertedMQ135(analogRead(0));
    float aqi = (DHT.humidity*.25) +(gc*.75);

    Serial.print(F(" AQI: "));
    Serial.print(aqi);
    Serial.print(F(" Humidity: "));
    Serial.print(DHT.humidity);
    Serial.print(F(" Temperature: "));
    Serial.print(DHT.temperature);
    Serial.print(F("°C "));
    Serial.print(F(" Remarks: "));
    if(aqi>=0 && aqi<=50)
    {
      Serial.println("GOOD");    
      }
    else if(aqi>=51 && aqi<=100)
    {
      Serial.println("MODERATE");
      }
    else if(aqi>=101 && aqi<=200)
    {
      Serial.println("UNHEALTHY");
      }  
    else if(aqi>=201 && aqi<=300)
    {
      Serial.println("VERY UNHEALTHY");
      }  
    else if(aqi>=301 && aqi<=500)
    {
      Serial.println("HAZARDOUS");
      }
    else
    {
      Serial.println("UNDEFINED");
      }
    delay(3000);
    
}
