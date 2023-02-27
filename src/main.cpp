#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"

//need JSON objects to read the JSON coming from server for get
#define LED_PIN0 2 //not sure which pins to use since i cant test physically
#define LED_PIN1 23
#define LED_PIN2 4

void setup() {
  pinMode(LED_PIN0,OUTPUT);
  pinMode(LED_PIN1,OUTPUT);
  pinMode(LED_PIN2,OUTPUT);

  char * endpoint ="https://ecse-three-led-api.onrender.com";

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASS); // initiates connection
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected with IP Address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
if (WiFi.status() != WL_CONNECTED ){
  HTTPClient http;
  http.begin(endpoint);
  http.addHeader("X-API-KEY","Flora#5798");
  String http_response;
  int httpResponseCode = http.GET();

  if (httpResponseCode>0){
    
    Serial.print("HTTP Response code: ");
    Serial.print(httpResponseCode);
    Serial.print("Response from server:");
    http_response = http.getString();
    Serial.print(http_response);
  }
  else{
    Serial.print("Error code:");
    Serial.print(httpResponseCode);
  }
  http.end();
  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc,http_response);

  if (error){
    Serial.print("Deserialize failed: ");
    Serial.print(error.c_str());
    return;
  }

  const bool LED0_state= doc["light0"];
  const bool LED1_state= doc["light1"];
  const bool LED2_state= doc["light2"];
if(LED0_state==1){
  digitalWrite(LED_PIN0,HIGH);
    delay(100);
    digitalWrite(LED_PIN0,LOW);
    delay(100);
}
if(LED1_state==1){
  digitalWrite(LED_PIN1,HIGH);
    delay(100);
    digitalWrite(LED_PIN1,LOW);
    delay(100);

}
if(LED2_state==1){
  digitalWrite(LED_PIN2,HIGH);
    delay(100);
    digitalWrite(LED_PIN2,LOW);
    delay(100);
}
}
else return;
  
  
}
