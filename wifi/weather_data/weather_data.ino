//***
//ArduinoJson biblioteka treba biti verzija 6.0 i više
//Struktuiranje json dokumenta se može uraditi na: https://jsonlint.com/
//aa3486d99e0a0e4c645643350a747a36
//***

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Gosti";
const char* password =  "preda2020";
 
const String server = "https://api.met.no/weatherapi/locationforecast/2.0/compact?lat=45.9799&lon=16.7140";
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  
}
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin(server); //Specify the URL
    int httpCode = http.GET();  //Make the request
 
    if (httpCode > 0) { //Check for the returning code

        DynamicJsonDocument doc(2048);
        
        String input = http.getString();
        Serial.println(httpCode);
        Serial.println(input);

        deserializeJson(doc, input);
        //JsonObject obj = doc.as<JsonObject>();

  // You can use a String to get an element of a JsonObject
  // No duplication is done.
  String weather = doc["properties"]["timeseries"][0]["data"]["next_6_hours"]["details"]["precipitation_amount"];
 
  Serial.print("Očekivane padavine u narednih 6 časova: ");
  Serial.print(weather);
  Serial.println(" mm"); 

  //Konverzija u integer varijablu ako želimo manipulisati sa vrijednošću (sabirati, oduzimati i sl.)
  int padavine = weather.toInt();
  //Serial.println(padavine);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
  delay(30000);
 
}
