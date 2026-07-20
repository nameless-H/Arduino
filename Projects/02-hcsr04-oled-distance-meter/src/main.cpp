#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin (-1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C 

const int trigPin = 9; // HC-SR04 trigger pin
const int echoPin = 10; // HC-SR04 echo pin

float readDistance(); // function to read distance using HC-SR04

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long lastTime = 0;
const long interval = 500; // ms

float distance = 0.0;

void setup()
{
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Initialize display with 3.3V internal charge pump
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }

    display.setTextSize(2); // Text scale set to 2:1
    display.setTextColor(SSD1306_WHITE); // Text color set to white
}

void loop()
{
    unsigned long currentTime = millis();

    if (currentTime - lastTime >= interval) 
    {
        lastTime = currentTime;
        
        distance = readDistance();

        display.clearDisplay();
        display.setCursor(0, 0);

        // Print Distance on OLED display
        display.println(F("Distance:"));

        if (distance < 0) {
            display.println(F("Out of"));
            display.println(F("range"));
        } else {
            display.print(distance);
            display.println(F(" cm"));
        }

        display.display();
    }
}

float readDistance() 
{
    // Clear trigger Pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Send a 10-microsecond pulse
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read pulse duration 
    long duration = pulseIn(echoPin, HIGH, 30000);
    
    // return -1 if out of range
    if (duration == 0) 
    {
        return -1.0; // Return -1 if object is out of range / timed out
    }

    return (duration * 0.0343) / 2.0;
}
