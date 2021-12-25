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
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
