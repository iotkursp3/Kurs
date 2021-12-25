#include "LoRa.h"
#include "ArduinoJson.h"

#define SCK 18
#define MISO 19
#define MOSI 23
#define SS 5
#define RST 14
#define DIO0 2

#define BAND 433E6

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)){
    Serial.println("LoRa init failed. Check your connections.");
    delay(500);
    ESP.restart();
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
