// token from blynk web console
#define BLYNK_TEMPLATE_ID "TMPL3oteM75lR"
#define BLYNK_TEMPLATE_NAME "automatic water pump"
#define BLYNK_AUTH_TOKEN "8A1WGda6GOzlbBsKwKRSJWIeEs5mIArm"


#define BLYNK_PRINT Serial

// required libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Redmi 9 Prime";
char pass[] = "00000000";


// pin descripion
int trigpin = D4;
int echopin = D5;
int pumppin = D1;
int traveltime;
int distance;
int level;


// on/off pump from blynk app


BLYNK_WRITE(V0)
{
  int value = param.asInt();
  digitalWrite(D1,value);
}



void setup() {
  pinMode(trigpin,OUTPUT);
  pinMode(pumppin,OUTPUT);
  pinMode(echopin,INPUT);
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  
  

}

void loop() {

  digitalWrite(trigpin,LOW);
  delayMicroseconds(1);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(2);
  digitalWrite(trigpin,LOW);
  delayMicroseconds(1);
  traveltime = pulseIn(echopin,HIGH);
  delayMicroseconds(10);

  distance = traveltime*(0.0367/2);

  level = 100 - distance;

  Serial.println(distance);
  Serial.println(level);


  Blynk.virtualWrite(V1,level);
  Blynk.run();



  if(distance>=100){
    digitalWrite(pumppin,HIGH);
      
  }

  if(distance<=10){
    digitalWrite(pumppin,LOW);
  }
    
 

  

}