# Fundamentals

This directory houses a collection of foundational exercises designed to master core Arduino concepts and essential hardware programming principles. These implementations establish a solid technical baseline for scaling into advanced embedded systems projects.

## Current Exercises:

### 1. FSM LED Blink
The most basic Arduino program, implemented as a Finite State Machine (FSM) to establish a clean architectural baseline. 
- Utilizes `unsigned long` time tracking via `millis()` instead of blocking `delay()` loops, keeping the CPU free for other processes.
- Implements delta-time comparison (`now - lastTransitionTime >= blinkInterval`) to natively handle `millis()` roll-over occurrences seamlessly.
- Uses an explicit `enum` for state definitions (`LED_OFF`, `LED_ON`) paired with a structured `switch-case` block to drive clean, predictable state transitions.

### 2. Button Debouncer
A time-triggered state machine designed to eliminate contact bounce—the noisy electrical signals produced when a physical mechanical button is toggled.
- Monitors shifts in the raw digital hardware reading to detect changes and reset an internal stability timer.
- Suppresses transient noise by ensuring the physical button reading remains perfectly stable for a defined debounce window before registering a valid toggle.
- Couples debouncing logic directly with a structured state system (`BUTTON_RELEASED`, `BUTTON_PRESSED`), demonstrating how to handle physical user input reliably.
