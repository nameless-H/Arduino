#include <Arduino.h>

enum ledState {
  FADING_UP,
  FADING_DOWN
};
ledState currentState = FADING_UP;


unsigned long lastStepTime = 0;
const unsigned long stepInterval = 10; //ms
int brightness = 0;
const int ledPin = 9;

void setup() {
  pinMode (ledPin, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  
  if (now - lastStepTime >= stepInterval) {
    lastStepTime = now;

    switch (currentState) {
      case FADING_UP:
        analogWrite(ledPin, brightness);
        if (brightness >= 255) {
          currentState = FADING_DOWN;
          break; 
        }
        brightness++;
        break;
      case FADING_DOWN:
        analogWrite(ledPin, brightness);
        if (brightness <= 0) {
          currentState = FADING_UP;
          break;
        }
        brightness--;
        break;
    }
  }
}
