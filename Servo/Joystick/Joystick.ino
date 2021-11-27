// These constants won't change. They're used to give names to the pins used:
const int xAxisPin = 26;
const int yAxisPin = 25;

void setup() {
  pinMode(xAxisPin, INPUT);
  pinMode(yAxisPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  // read the analog in value:
  int xAxisValue = 0;        // value read from the pot
  int yAxisValue = 0;  
  
  xAxisValue = analogRead(xAxisPin);
  yAxisValue = analogRead(yAxisPin);

  // print the results to the Serial Monitor:
  Serial.print("X: ");
  Serial.print(xAxisValue);
  Serial.print("  Y: ");
  Serial.print(yAxisValue);
  
  delay(2);
}
