// Koristićemo varijablu ledPin da označimo pin na koji ćemo povezati LED diodu
// varijabli ledPin dajemo vrijednost 23 (pin 23 na ESP32 pločici)
const int ledPin = 14;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin ledPin as an output.
  pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                  // wait for a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                  // wait for a second
}
