# Fundamentals

This directory houses a collection of foundational exercises designed to master core Arduino concepts and essential hardware programming principles. These implementations establish a solid technical baseline for scaling into advanced embedded systems projects.

## Current Exercises:

### 1. FSM LED Blink
The most basic Arduino program, implemented as a Finite State Machine (FSM) to establish a clean architectural baseline. 
- Non-Blocking Architecture: Utilizes `unsigned long` time tracking via `millis()` instead of blocking `delay()` loops, keeping the CPU free for other processes.
- Overflow Resilience: Implements delta-time comparison (`now - lastTransitionTime >= blinkInterval`) to natively handle `millis()` roll-over occurrences seamlessly.
- State Management: Uses an explicit `enum` for state definitions (`LED_OFF`, `LED_ON`) paired with a structured `switch-case` block to drive clean, predictable state transitions.

### 2. Button Debouncer
A time-triggered state machine designed to eliminate contact bounce—the noisy electrical signals produced when a physical mechanical button is toggled.
- Edge Detection: Monitors shifts in the raw digital hardware reading to detect changes and reset an internal stability timer.
- Time-Gated Verification: Suppresses transient noise by ensuring the physical button reading remains perfectly stable for a defined debounce window before registering a valid toggle.
- FSM Integration: Couples debouncing logic directly with a structured state system (`BUTTON_RELEASED`, `BUTTON_PRESSED`), demonstrating how to handle physical user input reliably.

### 3. PWM LED Dimmer
A time-triggered state machine demonstrating Pulse Width Modulation (PWM) to create a smooth, non-blocking LED fade effect.
- Pulse Width Modulation (PWM): Utilizes `analogWrite()` to dynamically adjust the output duty cycle, simulating variable analog voltage to smoothly control the perceived brightness of the LED.
- Continuous State Actions: Expands upon the basic FSM architecture by performing continuous, incremental actions (`brightness++` / `brightness--`) within an active state, rather than just executing a single discrete toggle.
- Threshold-Triggered Transitions: Evaluates dynamic boundary limits (`>= 255` and `<= 0`) to trigger state reversals seamlessly while maintaining a non-blocking execution loop.