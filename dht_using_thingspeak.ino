#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN 2

DHT dht(DHTPIN, DHT11,15);

#define LED D0
#define FAN D1

char ssid[] = "ZTE-87eeb4";          //  your network SSID (name) 
char pass[] = "8ce11787";     // your network password

int status = WL_IDLE_STATUS;
WiFiClient  client;

unsigned long myChannelNumber = 519632; 
const char * myReadAPIKey = "5R842Y5GTR182Y8J";
const char * myWriteAPIKey = "DB9SU6YZUB629SZQ";
void setup() {
  Serial.begin(9600); // for debugging reasons
  Serial.println("hello");
  delay(10);
  dht.begin();
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  ThingSpeak.begin(client);

}

void loop() 
{
  Serial.println("world");
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) 
  {
        Serial.println(".");
        return;
  }
 
    ThingSpeak.setField(1,t);
    ThingSpeak.setField(2,h);
  //  ThingSpeak.setField(6,LDR);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
   
 
  

  Serial.print("Temperature = ");Serial.println(t);  
  Serial.print (h);
  delay(1000);
}


