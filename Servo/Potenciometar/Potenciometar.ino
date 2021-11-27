// These constants won't change. They're used to give names to the pins used:
const int potentiometerPin = 25;  // Analog input pin that the potentiometer is attached to

void setup() {
  Serial.begin(115200);
}

void loop() {
  // read the analog in value:
  int pot_value = 0;        // value read from the pot
  pot_value = analogRead(potentiometerPin);

  // print the results to the Serial Monitor:
  Serial.print("Pozicija potenciometra: ");
  Serial.println(pot_value);
  
  delay(2);
}
