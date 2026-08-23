# OfflineController

Offline controller for manual control of an embedded system.

## About

**OfflineController** is an embedded project designed to provide a simple local interface for controlling a device without requiring a PC, smartphone, or network connection.

The project is being developed as a practical embedded systems project with a focus on:

* microcontroller programming;
* hardware control;
* buttons and user input;
* display interface;
* modular C++ code;
* device state management;
* future expansion with additional control functions.

## Project Status

**Version:** 0.1
**Status:** In development

The project is currently at an early development stage. The basic project structure has been created, and hardware and software functionality will be added incrementally.

## Main Goals

* Create a standalone offline controller.
* Implement a simple user interface.
* Control the target device using physical buttons.
* Display current device status and parameters.
* Keep the firmware modular and easy to maintain.
* Develop reusable drivers for hardware components.

## Hardware

The exact hardware configuration is still being developed.

Planned components may include:

* Microcontroller
* OLED display
* Control buttons
* Status indicators
* Additional input devices

## Software

The project is developed using:

* C++
* Arduino Framework
* PlatformIO

The firmware is organized into separate modules and drivers where possible.

## Project Structure

```text
OfflineController/
├── include/
├── lib/
├── src/
├── test/
├── .gitignore
├── platformio.ini
└── README.md
```

## Development

This project is actively under development. New hardware features, drivers, and control functionality will be added over time.

## Version History

### v0.1

* Initial project repository created.
* Basic project structure established.
* Git repository initialized.
* README added.
