# HC-SR04 OLED Distance Meter

Reads distance from an HC-SR04 ultrasonic sensor every 500 ms and displays it on an SSD1306 OLED screen over I2C. Handles out-of-range limits and sensor timeouts gracefully with clear status messages.

## Hardware

| Component                         | Quantity | Connection                   |
|-----------------------------------|----------|------------------------------|
| Arduino Uno R3                    | 1        | —                            |
| HCSR04 sensor                     | 1        | Trig → Pin 9, Echo → Pin 10  |
| SSD1306 0.96" OLED I2C display    | 1        | SDA → A4, SCL → A5           |
| Jumper wires                      | 8        | Vcc, GND, Signal lines       |

---

## Build & Flash

```bash
git clone https://github.com/nameless-H/Arduino.git
cd Arduino/Projects/01-hcsr04-oled-distance-meter
pio run --target upload
```

---

## What This Demonstrates

- Interfacing with an SSD1306 OLED screen over I2C using `Adafruit_SSD1306` and `Adafruit_GFX` libraries
- Precise timing measurement via 10 microsecond trigger pulses and `pulseIn()`
- Preventing code lockup by configuring a custom timeout parameter on `pulseIn()` (30,000 µs)
- Ultrasonic distance calculation converted from speed of sound constants using formula `(duration * 0.0343) / 2.0`
- Out-of-range and signal-loss detection with fallback UI feedback ("Out of range")

---

## Sample Output



---

## Dependencies

```ini
lib_deps = adafruit/Adafruit SSD1306@^2.5.17
```