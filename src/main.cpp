#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"

//need JSON objects to read the JSON coming from server for get
#define LED_PIN0 2
#define LED_PIN1 3
#define LED_PIN2 4

void setup() {
  pinMode(LED_PIN0,OUTPUT);
  pinMode(LED_PIN1,OUTPUT);
  pinMode(LED_PIN2,OUTPUT);

  char * endpoint = "https: //ecse-three-led-api.onrender.com";

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

 digitalWrite(LED_PIN0,HIGH);
    delay(500);
    digitalWrite(LED_PIN0,LOW);
    delay(500);

  digitalWrite(LED_PIN1,HIGH);
    delay(500);
    digitalWrite(LED_PIN1,LOW);
    delay(500);

  digitalWrite(LED_PIN2,HIGH);
    delay(500);
    digitalWrite(LED_PIN2,LOW);
    delay(500);
}
}
