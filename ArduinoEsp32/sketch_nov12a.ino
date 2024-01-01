#include "ModelDT.h"
Eloquent::ML::Port::DecisionTree clf;
#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebSrv.h>
  #include <SPIFFS.h>
#else
  #include <WiFi.h>
#endif
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

// Replace with your network credentials
const char* ssid = "kien123";
const char* password = "12345678";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readBME280Temperature() {
  // Read temperature as Celsius (the default)
  float t = bme.readTemperature();
  // Convert temperature to Fahrenheit
  //t = 1.8 * t + 32;
  if (isnan(t)) {    
    Serial.print("Failed to read from BME280 sensor!");
    return "";
  }
  else {
    Serial.print(t);
    Serial.print(",");
    return String(t);
  }
}

String readBME280Humidity() {
  float h = bme.readHumidity();
  if (isnan(h)) {
    Serial.print("Failed to read from BME280 sensor!");
    return "";
  }
  else {
    Serial.print(h);
    Serial.print(",");
    return String(h);
  }
}

String readBME280Pressure() {
  float p = bme.readPressure() / 100.0F;
  if (isnan(p)) {
    Serial.println("Failed to read from BME280 sensor!");
    return "";
  }
  else {
    Serial.println(p);
    return String(p);
  }
}
String Predict() {
  float t = bme.readTemperature(); // temperature
  float h = bme.readHumidity();  // humidity
  float p = bme.readPressure() / 100.0F;   // pressure
  float irisSample[3] = {t, h, p};
  Serial.println(clf.predict(irisSample));
  String pre = String(clf.predict(irisSample));
  String result;
  if(pre == "0")
  {result = "Cold fog";}
  else if(pre == "1")
  {result = "Rainy";}
  else if(pre == "2")
  {result = "Sunny";}
  else if(pre == "3")
  {result = "blazing_sun";}
  else if(pre == "4")
  {result = "lightly_sunlit";}
  else
  {result = "pleasantly cool";}
  //
  
  //
  return String(result);
}
void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  bool status; 
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBME280Temperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBME280Humidity().c_str());
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readBME280Pressure().c_str());
  });
   server.on("/predict", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", Predict().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
   if(WiFi.status()== WL_CONNECTED){
  float t = bme.readTemperature(); // temperature
  float h = bme.readHumidity();  // humidity
  float p = bme.readPressure() / 100.0F;   // pressure
  float irisSample[3] = {t, h, p};
  Serial.println(clf.predict(irisSample));
  String pre = String(clf.predict(irisSample));
  String result;
  if(pre == "0")
  {result = "Cold fog";}
  else if(pre == "1")
  {result = "Rainy";}
  else if(pre == "2")
  {result = "Sunny";}
  else if(pre == "3")
  {result = "blazing_sun";}
  else if(pre == "4")
  {result = "lightly_sunlit";}
  else
  {result = "pleasantly cool";}
  //
  StaticJsonDocument<200> doc;
   doc["temp"] = String(t);
   doc["humidity"] = String(h);
   doc["pressure"] = String(p);
   doc["predict"] = String(result);

   String requestBody;
   serializeJson(doc, requestBody);
   HTTPClient http;
   Serial.println(requestBody);
   http.begin("https://serverweather.azurewebsites.net/api/weather1");
   http.addHeader("Content-Type", "application/json");
   int httpResponseCode = http.POST(requestBody);
   if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.print("Response: ");
        Serial.println(response);
    } else {
        Serial.print("Error on sending POST: ");
        Serial.println(httpResponseCode);
    }

    http.end();
   }
   else{
  
    Serial.println("Error in WiFi connection");   
  
 }
  
  delay(10000);
}
