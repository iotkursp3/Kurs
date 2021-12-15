#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

#include "DHT.h"

// Replace the next variables with your SSID/Password combination
const char* ssid = "Gosti";
const char* password = "preda2020";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "io.adafruit.com";

//Dodati kredencijale sa kojima smo se registrovali na AdafruitIO:
#define mqtt_user "USERNAME"
#define outTopic  "USERNAME/F/onoffbutton"
#define mqtt_key  "ZAMIJENITI_SA_VAŠIM_API_KLJUCEM"

//DHT11 senzor:
#define DHTPIN 13
//our sensor is DHT11 type
#define DHTTYPE DHT11
//create an instance of DHT sensor
DHT dht(DHTPIN, DHTTYPE);

//Deklariši wifi klijenta i pubsub klijenta:
WiFiClient espClient;
PubSubClient client(espClient);

//Varijable za preuzimanje mqtt poruka:
long lastMsgTime = 0;
char msg[50];
int value = 0;

//Varijable za DHT11 senzor:
float temperature = 0;
float humidity = 0;

// Varijabla za LED Pin:
const int ledPin = 16;


void setup() {
  Serial.begin(115200);
  
  //call begin to start sensor
  dht.begin();
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(ledPin, OUTPUT);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//Glavni dio za prijem mqtt poruka:
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String newMessage;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    newMessage += (char)message[i];
  }
  Serial.println();

  // Ako primljena poruka ima topic "onoffbutton", provjeri da li poruka glasi "ON" ili "OFF". 
  if (String(topic) == (String(mqtt_user) + String("/feeds/onoffbutton"))) {
    Serial.print("Mijenjam stanje led-a u: ");
    if(newMessage == "ON"){
      Serial.println("ON");
      digitalWrite(ledPin, HIGH);   //Upali led
    }
    else if(newMessage == "OFF"){
      Serial.println("OFF");
      digitalWrite(ledPin, LOW);    //Ugasi led
    }
  }
  
  // Feel free to add more if statements to control more GPIOs with MQTT
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),mqtt_user, mqtt_key)) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("USERNAME/feeds/onoffbutton");           //Ovdje obavezno ubaciti topic za subscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
//Provjera jesmo li povezani na mqtt server:
  if (!client.connected()) {
    reconnect();        //ako nismo, ponovi konekciju
  }
  client.loop();        //ako jesmo nastavi sa loop-om

//Definiši pomoću milisa interval očitavanja podataka sa senzora (svakih 5 sek.):
  long now = millis();
  if (now - lastMsgTime > 5000) {
    lastMsgTime = now;
    
    //Očitaj podatke sa senzora:
    //humidity = dht.readHumidity();
    humidity = 20;      //samo za test, bez senzora
    //temperature = dht.readTemperature();
    temperature = 10;   //samo za test, bez senzora
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }
    
    // Convert the value to a char array
    char tempString[8];
    dtostrf(temperature, 1, 2, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
    client.publish("USERNAME/feeds/photocell", tempString);   //Adafruit IO zahtjeva ovaj format topic-a: {your Adafruit IO username}/feeds/{feed key}

    /*
    // Convert the value to a char array
    char humString[8];
    dtostrf(humidity, 1, 2, humString);
    Serial.print("Humidity: ");
    Serial.println(humString);
    client.publish("USERNAME/feeds/photocell", humString);    //Adafruit IO zahtjeva ovaj format topic-a: {your Adafruit IO username}/feeds/{feed key}
    */
  }
}
