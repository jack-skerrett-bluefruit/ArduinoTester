#include "HX711.h"
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
int LEDup = 5;
int LEDdown = 9;
int buttonPin = 12;
long maxpower;
long minpower;
auto buttonPress = HIGH;
int PWM_OUTPUT_BLUE = 0;
int PWM_OUTPUT_ORANGE = 0;
int centrePoint = -20000;
HX711 scale;
void setup() {
  Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  pinMode(LEDup, OUTPUT);
  pinMode(LEDdown, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}
void loop() {
  buttonPress = digitalRead(12);
  if (buttonPress != HIGH) {
    calibrate();
  } else {
    // Serial.println("You are not calibrating");
    long reading;
    if (scale.is_ready()) {
      reading = scale.read();
      Serial.print("reading = ");
      Serial.print(reading);
      Serial.print("    ");
      //Serial.print("HX711 reading: ");
      //Serial.println(reading);
    } else {
      //Serial.println("HX711 not found.");
    }
    if (reading > maxpower || reading < minpower) {
      Serial.println("out of bounds");
    }
    if (reading > centrePoint)
    {
      PWM_OUTPUT_BLUE = map(reading, centrePoint, maxpower, 0, 255);
      if(PWM_OUTPUT_BLUE > 255){
        Serial.print("YOURE A FUCKWIT");
        PWM_OUTPUT_BLUE = 255;
      } else if (PWM_OUTPUT_BLUE <= 0){
        PWM_OUTPUT_BLUE = 0;
      }
      analogWrite(LEDup, PWM_OUTPUT_BLUE);
    } else if (reading < centrePoint) {
      PWM_OUTPUT_ORANGE = map(reading, centrePoint, minpower, 0, 255);
      if(PWM_OUTPUT_ORANGE > 255){
        PWM_OUTPUT_ORANGE = 255;
      } else if (PWM_OUTPUT_ORANGE <= 0){
        PWM_OUTPUT_ORANGE = 0;
      }
      analogWrite(LEDdown, PWM_OUTPUT_ORANGE);
    }
    Serial.print("MIN ");
    Serial.print(minpower);
    Serial.print(" MAX ");
    Serial.print(maxpower);
    Serial.print(" BLUE LED LEVEL  ");
    Serial.print(PWM_OUTPUT_BLUE);
    Serial.print(" ORANGE LED LEVEL ");
    Serial.println(PWM_OUTPUT_ORANGE);
    delay(100);
  }
}
void calibrate()
{
  Serial.println("You are calibrating");
  if (scale.is_ready())
  {
    auto reading = scale.read();
    if (reading > maxpower) {
      maxpower = reading;
      Serial.print("new max power reading of ");
      Serial.println(maxpower);
    }
    else if (reading < minpower) {
      minpower = reading;
      Serial.print("new min power reading of ");
      Serial.println(minpower);
    }
  }
}
