#include <WiFi.h>
#include <ThingSpeak.h>
#include <stdio.h>
#include "DHTesp.h"

int ledPin = 2; 
int ledPin2 = 4;      
int ledPin3 = 5;   
int ledPin4 = 19;   // choose the pin for the LED
int inputPin = 13; 
int inputPin2 = 12; 
int inputPin3 = 14;   
int inputPin4 = 26;              // choose the input pin (for PIR senso
int val = 0; 
int val2 = 0;    
int val3 = 0; 
int val4 = 0; 

DHTesp dhtSensor;
TempAndHumidity data;
const int DHT_PIN = 33;

char ssid[] = "Wokwi-GUEST";
char pass[] = ""; 
int pir[]={0,0,0,0};
WiFiClient client;
unsigned long myChannelNumber = write your channel number;
const char * myWriteAPIKey = "write your API key";

int statusCode;

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
   pinMode(ledPin2, OUTPUT);      // declare LED as output
  pinMode(inputPin2, INPUT);
  pinMode(ledPin3, OUTPUT); 
  pinMode(inputPin3, INPUT);
  pinMode(ledPin4, OUTPUT); 
  pinMode(inputPin4, INPUT);

  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);

  Serial.begin(9600);
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client);

}


void loop() {
  connectToCloud();
  val = digitalRead(inputPin);
  val2 = digitalRead(inputPin2);
  val3 = digitalRead(inputPin3);
  val4 = digitalRead(inputPin4);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pir[0] == 0) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pir[0] = 1;
       
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pir[0] == 1) {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
     pir[0] = 0;
    }
  }

  if (val2 == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin2, HIGH);  // turn LED ON
    if (pir[1] == 0) {
      // we have just turned on
      Serial.println("Motion2 detected!");
      // We only want to print on the output change, not state
      pir[1] = 1;
    }
  } else {
    digitalWrite(ledPin2, LOW); // turn LED OFF
    if (pir[1] == 1) {
      // we have just turned of
      Serial.println("Motion2 ended!");
      // We only want to print on the output change, not state
     pir[1] = 0;
    }
  }

  if (val3 == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin3, HIGH);  // turn LED ON
    if (pir[2] == 0) {
      // we have just turned on
      Serial.println("Motion3 detected!");
      // We only want to print on the output change, not state
      pir[2] = 1;
    }
  } else {
    digitalWrite(ledPin3, LOW); // turn LED OFF
    if (pir[2] == 1) {
      // we have just turned of
      Serial.println("Motion3 ended!");
      // We only want to print on the output change, not state
      pir[2] = 0;
    }
  }
  if (val4 == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin4, HIGH);  // turn LED ON
    if (pir[3] == 0) {
      // we have just turned on
      Serial.println("Motion3 detected!");
      // We only want to print on the output change, not state
      pir[3] = 1;
    }
  } else {
    digitalWrite(ledPin4, LOW); // turn LED OFF
    if (pir[3] == 1) {
      // we have just turned of
      Serial.println("Motion3 ended!");
      // We only want to print on the output change, not state
      pir[3] = 0;
    }
  }
 

   for(int i=0;i<4;i++) {

    ThingSpeak.setField(i+1 , pir[i]);
}
 data = dhtSensor.getTempAndHumidity();
  Serial.println("Humi: " + String(data.humidity));
  Serial.println("Temp: " + String(data.temperature));
ThingSpeak.setField(5 ,data.humidity);
ThingSpeak.setField(6,data.temperature );
        statusCode = ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
        if(statusCode == 200) //successful writing code
        Serial.println("Channel update successful.");
        else
        Serial.println("Problem Writing data. HTTP error code :" +
        String(statusCode));
      // data to be uploaded 
    delay(15000); 
}

void connectToCloud(){
if(WiFi.status() != WL_CONNECTED) {
Serial.print("Attempting to connect");
while(WiFi.status() != WL_CONNECTED) {
WiFi.begin(ssid, pass);
for(int i=0;i<5;i++) {
Serial.print(".");
delay(1000);
}
}
Serial.println("\nConnected.");
}
}
