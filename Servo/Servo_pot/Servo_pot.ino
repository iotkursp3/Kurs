#include <Servo.h>

static const int servoPin = 13;
static const int potentiometerPin = 25;

Servo servo1;

void setup() {
    Serial.begin(115200);
    servo1.attach(servoPin);
}

void loop() {
    int pot_value = 0;        // value read from the pot
    pot_value = analogRead(potentiometerPin);

    // print the results to the Serial Monitor:
    Serial.print("Pozicija potenciometra: ");
    Serial.println(pot_value);
    
    int servoPosition = map(pot_value, 0, 4096, 0, 180);
    servo1.write(servoPosition);
    Serial.println(servoPosition);
    delay(20);
}
