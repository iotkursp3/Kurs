//Formatiranje vremena u c++
//https://www.cplusplus.com/reference/ctime/strftime/

#include <WiFi.h>
#include "time.h"

const char* ssid     = "Gosti";
const char* password = "preda2020";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;         //razlika u odnosu na UTC
const int   daylightOffset_sec = 3600;    //razlika za ljetno/zimsko računanje vremena

void setup(){
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

//Ispiši vrijeme kao char varijablu:
  Serial.println("Time variables");
  char timeHM[20]; //10 chars should be enough
  strftime(timeHM, 20, "%H:%M", &timeinfo);     //ovdje podešavamo šta želimo da nam ispiše - dan, sat, minut npr. "%H:%M" je sat:minut 
  Serial.println(timeHM);

//Definiši moje vrijeme za restart kao char varijablu:
  char mytimeHM[20] = "12:44";
  Serial.println(mytimeHM);

//Uslov za reset:
  if (strcmp(timeHM, mytimeHM)== 0) {
    Serial.println("Time for reset.");
    ESP.restart();
    //nakon reseta sačekaj 20 sec.  
    delay(20000);
  }
}

void loop(){
  delay(1000);
  printLocalTime();
}
