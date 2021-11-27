// These constants won't change. They're used to give names to the pins used:
const int xAxisPin = 25;
const int yAxisPin = 26;
static const int servoPin = 13;

Servo servo1;

void setup() {
  Serial.begin(115200);
  pinMode(xAxisPin, INPUT);
  pinMode(yAxisPin, INPUT);
  servo1.attach(servoPin);
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
  
  int servoPosition = map(xAxisValue, 0, 4096, 0, 180);
  servo1.write(servoPosition);
  Serial.println(servoPosition);
  
  delay(2);
}
