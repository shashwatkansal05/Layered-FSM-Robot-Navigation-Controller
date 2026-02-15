# Layered-FSM-Robot-Navigation-Controller
Overview

This project implements a robot navigation controller in C using a layered finite state machine (FSM) architecture.

The objective was to design firmware-style control logic instead of writing a monolithic loop-based program. The system is event-driven and modular, separating behavior logic from environment simulation.

The robot operates in a terminal-based simulated environment and demonstrates reactive navigation with mode control and obstacle handling.
---

Architecture

The system is divided into independent modules:

1. Mode FSM

Handles high-level operation modes:

AUTO

MANUAL

Responsible for deciding whether motion control should execute.

2. Motion FSM

Controls movement behavior:

Forward motion

Obstacle detection response

Escape/turn logic

3. Event Queue

Implements asynchronous communication between components.
All behavior transitions are triggered by events such as:

Timeout

Obstacle detection

User mode change

4. World Simulation Layer

Simulates:

Environment

Obstacles

Sensor triggers

Actuator output (visualization)

This layer is independent of firmware logic and acts as a test harness.

---
Project Structure

main.c
event_queue.c / event_queue.h
motion_fsm.c / motion_fsm.h
mode_fsm.c / mode_fsm.h
world_sim.c
action.h
event.h

---
MODE FSM STATE TABLE

| Current State | Event             | Next State | Action         |
| ------------- | ----------------- | ---------- | -------------- |
| AUTO          | EVENT_USER_MANUAL | MANUAL     | Disable motion |
| MANUAL        | EVENT_USER_AUTO   | AUTO       | Enable motion  |
| AUTO          | Other Events      | AUTO       | No change      |
| MANUAL        | Other Events      | MANUAL     | Ignore         |

MOTION FSM STATE TABLE

| Current State | Event          | Next State   | Action       |
| ------------- | -------------- | ------------ | ------------ |
| MOVE_FORWARD  | EVENT_TIMEOUT  | MOVE_FORWARD | Move forward |
| MOVE_FORWARD  | EVENT_OBSTACLE | TURN_RIGHT   | Turn right   |
| TURN_RIGHT    | EVENT_TIMEOUT  | MOVE_FORWARD | Move forward |
| TURN_RIGHT    | EVENT_OBSTACLE | TURN_RIGHT   | Keep turning |

---

Behavioral Summary

The Mode FSM operates at a higher level and can disable motion execution.

The Motion FSM reacts only to obstacle and timeout events.

All transitions are triggered through events from the event queue.

No state change occurs without an explicit event.
