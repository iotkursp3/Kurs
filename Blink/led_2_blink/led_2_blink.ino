const int ledPinCrvena = 14;
const int ledPinPlava = 27;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledPinCrvena, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(ledPinPlava, LOW);
  delay(1000);                  // wait for a second
  digitalWrite(ledPinCrvena, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ledPinPlava, HIGH);
  delay(1000);                  // wait for a second
}
