#include <Arduino.h>

enum AlarmState
{
  DISARMED,
  ARMING,
  ARMED,
  TRIGGERED,
  ALARM,
  COOLDOWN
};

AlarmState currentState = DISARMED;
AlarmState lastState = DISARMED;

const int ledPin = 9;
const int buttonPin = 3;
const int buzzerPin = 8;
const int pirPin = 2;

const unsigned long longPressThreshold = 1500; // ms
const unsigned long debounceDelay = 50;        // ms

bool buttonState = HIGH;

unsigned long stateEntryTime = 0;
const unsigned long armingTime = 10000;   // ms
const unsigned long graceTime = 5000;     // ms
const unsigned long cooldownTime = 30000; // ms

void handleButton();
void readButton();
void readPirSensor();
void updateLED();
void updateFSM();

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  readButton();
  handleButton();
  updateFSM();
  updateLED();
}

void readButton()
{
  static bool lastButtonReading = HIGH;
  static unsigned long lastDebounceTime = 0;

  int reading = digitalRead(buttonPin);

  if (reading != lastButtonReading)
  {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime >= debounceDelay)
  {
    buttonState = reading; // stable — trust it
  }

  lastButtonReading = reading;
}

void handleButton()
{
  static bool prevButtonState = HIGH;
  static unsigned long pressTime = 0;
  static bool longPressHandled = false;

  if (buttonState == LOW && prevButtonState == HIGH)
  {
    pressTime = millis();
    longPressHandled = false;
  }

  unsigned long pressDuration = millis() - pressTime;

  if (buttonState == LOW && !longPressHandled && pressDuration >= longPressThreshold)
  {
    currentState = (currentState == DISARMED) ? ARMING : DISARMED;
    longPressHandled = true;
  }

  if (buttonState == HIGH && prevButtonState == LOW && !longPressHandled)
  {
    if (currentState == TRIGGERED || currentState == ALARM)
      currentState = COOLDOWN;
  }

  prevButtonState = buttonState;
}

void readPirSensor()
{
  static int lastPirState = LOW;
  int currentPirState = digitalRead(pirPin);

  if (currentPirState == HIGH && lastPirState == LOW)
  {
    currentState = TRIGGERED;
  }

  lastPirState = currentPirState;
}

void printState(AlarmState state)
{
  switch (state)
  {
  case DISARMED:
    Serial.println("DISARMED");
    break;
  case ARMING:
    Serial.println("ARMING");
    break;
  case ARMED:
    Serial.println("ARMED");
    break;
  case TRIGGERED:
    Serial.println("TRIGGERED");
    break;
  case ALARM:
    Serial.println("ALARM");
    break;
  case COOLDOWN:
    Serial.println("COOLDOWN");
    break;
  }
}

void updateLED()
{
  static unsigned long lastToggle = 0;
  static bool ledState = LOW;
  unsigned long interval = 0;

  switch (currentState)
  {
  case DISARMED:
    digitalWrite(ledPin, LOW);
    break;
  case ARMING:
    interval = 100;
    break;
  case ARMED:
    break;
  case TRIGGERED:
    interval = 50;
    break;
  case ALARM:
    interval = 0;
  case COOLDOWN:
    unsigned long elapsedTime = millis() - stateEntryTime;
    if (elapsedTime < cooldownTime)
    {
      int brightness = map(elapsedTime, 0, cooldownTime, 255, 0);
      analogWrite(ledPin, brightness);
    }
    else
    {
      analogWrite(ledPin, 0);
    }
  }

  if (millis() - lastToggle >= interval && currentState != DISARMED && currentState != COOLDOWN)
  {
    lastToggle = millis();
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }
}

void updateFSM()
{

  if (currentState != lastState)
  {
    stateEntryTime = millis();
    Serial.print("State changed: ");
    printState(currentState);
    lastState = currentState;
  }

  switch (currentState)
  {
  case DISARMED:
    // Serial.println("DISARMED");
    break;
  case ARMING:
    if (millis() - stateEntryTime >= armingTime)
    {
      currentState = ARMED;
    }
    // Serial.println("ARMING");
    break;
  case ARMED:
    readPirSensor();
    // Serial.println("ARMED");
    break;
  case TRIGGERED:
    if (millis() - stateEntryTime >= graceTime)
    {
      currentState = ALARM;
    }
    // Serial.println("TRIGGERED");
    break;
  case ALARM:
    // Serial.println("ALARM");
    break;
  case COOLDOWN:
    if (millis() - stateEntryTime >= cooldownTime)
    {
      currentState = ARMED;
    }
    // Serial.println("COOLDOWN");
    break;
  }
}
