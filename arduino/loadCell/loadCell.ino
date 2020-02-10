#include "HX711.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
long maxpower;
long minpower;
auto buttonPress = HIGH;

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  pinMode(5, OUTPUT);
  pinMode(12, INPUT_PULLUP);
}

void calibrate() {
  Serial.println("You are calibrating");
  if (scale.is_ready()) {
    auto reading = scale.read();
    if (reading > maxpower) {
      maxpower = reading;
      Serial.println("new max power reading of" + maxpower);
    }
    if (reading < minpower) {
      minpower = reading;
      Serial.println("new min power reading of" + minpower);
    }

  }

}

void loop() {
  buttonPress = digitalRead(12);

  if (buttonPress != HIGH) {
    calibrate();
  } else {
    Serial.println("You are not calibrating");
    long reading;
    if (scale.is_ready()) {
      reading = scale.read();
      //Serial.print("HX711 reading: ");
      //Serial.println(reading);
    } else {
      //Serial.println("HX711 not found.");
    }

    int PWM_OUTPUT = map(reading, minpower, maxpower, 0, 255);
    if (PWM_OUTPUT > 0 && PWM_OUTPUT) {
      Serial.println(PWM_OUTPUT);
      analogWrite(5, PWM_OUTPUT);
    } 
    delay(100);
  }
}
