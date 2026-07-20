# Temperature & Humidity Logger

Reads temperature and humidity from a DHT11 sensor every 2 seconds and logs timestamped readings over Serial. Detects and reports sensor faults (loose wire, missing sensor) instead of printing corrupt data.

---

## Hardware

| Component         | Quantity | Connection         |
|-------------------|----------|--------------------|
| Arduino Uno R3    | 1        | —                  |
| DHT11 sensor      | 1        | Data → Pin 7       |
| Jumper wires      | 3        | VCC, GND, Data     |

---

## Build & Flash

```bash
git clone https://github.com/nameless-H/Arduino.git
cd Arduino/Projects/01-temp-humidity-logger
pio run --target upload
```

Open Serial Monitor at **9600 baud** to view output.

---

## What This Demonstrates

- Non-blocking sensor reads using `millis()` instead of `delay()`
- Structured Serial output with `millis()` timestamps
- NaN fault detection using `isnan()` — handles sensor disconnection gracefully without printing corrupt values
- Library integration via PlatformIO (`adafruit/DHT sensor library`)

---

## Sample Output

Normal operation:
```
[2000ms] Temperature: 27.00°C  Humidity: 73.00%
[4000ms] Temperature: 27.00°C  Humidity: 73.00%
[6000ms] Temperature: 27.00°C  Humidity: 74.00%
```

Fault condition (loose wire detected during testing):
```
[8000ms] Sensor read failed
[10000ms] Sensor read failed
[12000ms] Temperature: 27.00°C  Humidity: 73.00%
```

---

## Dependencies

```ini
lib_deps =
    adafruit/DHT sensor library @ ^1.4.6
    adafruit/Adafruit Unified Sensor @ ^1.1.9
```