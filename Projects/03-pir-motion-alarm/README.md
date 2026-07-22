# PIR Motion Sensor Alarm

Six-state finite state machine implementing a PIR motion alarm with arming sequence, grace period, active alarm, and timed cooldown — controlled by a single button using short press and long press detection.

---

## States

| State Name | Description                                               | LED Behavior    | Buzzer Behavior   |
|------------|-----------------------------------------------------------|-----------------|-------------------|
| `DISARMED`   | System off, ignores everything                            | OFF             | OFF               |
| `ARMING`     | Countdown after user arms it (time to leave the room)     | Fast Blink      | OFF               |
| `ARMED`      | Watching for motion                                       | Slow Heartbeat  | OFF               |
| `TRIGGERED`  | Motion detected, pre-alarm delay (grace period to disarm) | Very Fast Blink | OFF               |
| `ALARM`      | Full alarm active                                         | Solid ON        | Fast Beep (1 kHz) |
| `COOLDOWN`   | Alarm dismissed, brief lockout before re-arming           | Slow Fade Down  | OFF               |

---

## Transitions

| From State       | Event/Condition    | To State    |
|------------------|--------------------|-------------|
| `DISARMED`       | Long button press  | `ARMING`    |
| `ARMING`         | 10s timer          | `ARMED`     |
| `ARMED`          | Motion detected    | `TRIGGERED` |
| `TRIGGERED`      | 5s grace period    | `ALARM`     |
| `TRIGGERED`      | Short button press | `COOLDOWN`  |
| `ALARM`          | Short button press | `COOLDOWN`  |
| `COOLDOWN`       | 30s timer          | `IDLE`      |
| **Any State**    | Long button press  | `DISARMED`  |

---

## Hardware

| Component                  | Quantity | Connection          |
|----------------------------|----------|---------------------|
| Arduino Uno R3             | 1        | —                   |
| HC-SR501 PIR motion sensor | 1        | Out → Pin 2         |
| 5 mm LED                   | 1        | Anode(+) → Pin ~9   |
| Passive Buzzer             | 1        | Positive(+) → Pin 8 |
| Tactile Push Button        | 1        | Signal → Pin 3      |
| Jumper wires               | 8        | Vcc, GND, Signals   |

---

## Build & Flash

```bash
git clone https://github.com/nameless-H/Arduino.git
cd Arduino/Projects/03-pir-motion-alarm
pio run --target upload
```

---

## What This Demonstrates

- **Multi-state FSM architecture** — six states with both time-driven and event-driven transitions, modelling a real embedded control system rather than a simple toggle
- **Non-blocking timing** — independent `millis()` timers running in parallel for state duration, LED patterns, and buzzer cadence without any `delay()` calls
- **Single-button multi-function input** — short press and long press detection using press duration measurement, with debouncing and a `longPressHandled` flag to prevent repeated triggers
- **HAL separation** — hardware reading (`readButton()`, `readPirSensor()`) decoupled from application logic (`handleButton()`, `updateFSM()`) so input sources can be swapped without touching FSM code
- **State-driven output descriptor pattern** — `updateLED()` separates parameter definition (per-state `onTime`/`offTime`) from execution logic, making new states a one-line addition
- **PWM fade as a status indicator** — COOLDOWN state maps elapsed time to LED brightness using `map()` and `constrain()`, giving the user a visual representation of remaining cooldown time
- **Static local variables for persistent state** — debounce timers, press timestamps, and LED toggle state scoped to their respective functions rather than polluting global scope

---

## Demo

<img width="1094" height="416" alt="Screenshot From 2026-07-22 08-45-21" src="https://github.com/user-attachments/assets/290acbd8-964d-41e5-addf-ae0fce4b155c" />
