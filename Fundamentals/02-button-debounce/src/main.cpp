#include <Arduino.h>

enum ButtonState
{
  BUTTON_RELEASED,
  BUTTON_PRESSED
};
ButtonState currentState = BUTTON_RELEASED;

const int buttonPin = 2;
const int ledPin = 13;
const unsigned long debounceDelay = 50; // ms

int lastRawReading = LOW;
unsigned long lastBounceTime = 0;

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int reading = digitalRead(buttonPin);

  if (reading != lastRawReading)
  {
    lastBounceTime = millis();
    Serial.print("RAW CHANGE = ");
    Serial.println(reading);
  }

  if ((millis() - lastBounceTime) > debounceDelay)
  {
    // reading has been stable for longer than debounceDelay — trust it
    switch (currentState)
    {
    case BUTTON_RELEASED:
      if (reading == HIGH)
      {
        currentState = BUTTON_PRESSED;
        digitalWrite(ledPin, HIGH);
        Serial.println("STATE = PRESSED");
      }
      break;

    case BUTTON_PRESSED:
      if (reading == LOW) 
      {
        currentState = BUTTON_RELEASED;
        digitalWrite(ledPin, LOW);
        Serial.println("STATE = RELEASED");
      }
      break;
    }
  }
  lastRawReading = reading;
}