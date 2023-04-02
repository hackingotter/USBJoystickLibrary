# USBJoystickLibrary

This library is based on the [ArduinoJoystickLibrary by Matthew Heironimus](https://github.com/MHeironimus/ArduinoJoystickLibrary) and the [Keyboard Class](https://github.com/arduino/ArduinoCore-mbed/blob/master/libraries/USBHID/src/USBKeyboard.cpp) provided in [ArduinoCore-mbed](https://github.com/arduino/ArduinoCore-mbed). 

It ports the ArduinoJoystickLibrary (V2.1.1) to be built ontop of the mbed USBHID library. This allows it to run on mbed platforms such as the RP2040 in the Raspberry Pi Pico.

On the Pico, it is supposed to run on the default Arduino board definition for the RP2040 (Arduino mbed OS RP2040).

## Version 0.9.0

This is the initial version. It has been smoke tested with 1 axis on a Raspberry Pi Pico but nothing more.

## Features

(Same as ArduinoJoystickLibrary) 

The joystick or gamepad can have the following features:

    Buttons (default: 32)
    Up to 2 Hat Switches
    X, Y, and/or Z Axis (up to 16-bit precision)
    X, Y, and/or Z Axis Rotation (up to 16-bit precision)
    Rudder (up to 16-bit precision)
    Throttle (up to 16-bit precision)
    Accelerator (up to 16-bit precision)
    Brake (up to 16-bit precision)
    Steering (up to 16-bit precision)

## Installation Instructions

The following instructions can be used to install the latest version of the library in the Arduino IDE:

1. Download https://github.com/hackingotter/USBJoystickLibrary/archive/master.zip
2. In the Arduino IDE, select `Sketch` > `Include Library` > `Add .ZIP Library...`.  Browse to where the downloaded ZIP file is located and click `Open`. The Joystick library's examples will now appear under `File` > `Examples` > `Joystick`.

### Simple example

```C++
#include "USBJoystick.h"
// it is important to make this instance here. If done in setup() it seems to be too late to work properly. The USB device just doesn't come up right
Joystick_ *Joystick = new Joystick_(); 

void setup() {
  // Initialize Joystick Library
  Joystick->setXAxisRange(0, 1024);
  Joystick->begin(true);
}

void loop() {
  int xAxis;
  // read analog value and assign it to the joystick axis
  xAxis = analogRead(A0);
  Joystick->setXAxis(xAxis);
  sleep_ms(50);
}
```

### More examples

For more examples, see the original [ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/master/examples).

The external API for this library is the same as for the original one (V2.1.1) so the examples will work with this library as well.

## Joystick Library API

The following API is available if the Joystick library in included in a sketch file.

### Joystick\_(...)

Constructor used to initialize and setup the Joystick. The following optional parameters are available:

- `uint8_t hidReportId` - Default: `0x03` - Indicates the joystick's HID report ID. This value must be unique if you are creating multiple instances of Joystick. Do not use `0x01` or `0x02` as they are used by the built-in Arduino Keyboard and Mouse libraries.
- `uint8_t joystickType` - Default: `JOYSTICK_TYPE_JOYSTICK` or `0x04` - Indicates the HID input device type. Supported values:
  - `JOYSTICK_TYPE_JOYSTICK` or `0x04` - Joystick 
  - `JOYSTICK_TYPE_GAMEPAD` or `0x05` - Gamepad
  - `JOYSTICK_TYPE_MULTI_AXIS` or `0x08` - Multi-axis Controller 
- `uint8_t buttonCount` - Default: `32` - Indicates how many buttons will be available on the joystick.
- `uint8_t hatSwitchCount` - Default: `2` - Indicates how many hat switches will be available on the joystick. Range: `0` - `2`
- `bool includeXAxis` - Default: `true` - Indicates if the X Axis is available on the joystick.
- `bool includeYAxis` - Default: `true` - Indicates if the Y Axis is available on the joystick.
- `bool includeZAxis` - Default: `true` - Indicates if the Z Axis (in some situations this is the right X Axis) is available on the joystick.
- `bool includeRxAxis` - Default: `true` - Indicates if the X Axis Rotation (in some situations this is the right Y Axis) is available on the joystick.
- `bool includeRyAxis` - Default: `true` - Indicates if the Y Axis Rotation is available on the joystick.
- `bool includeRzAxis` - Default: `true` - Indicates if the Z Axis Rotation is available on the joystick.
- `bool includeRudder` - Default: `true` - Indicates if the Rudder is available on the joystick.
- `bool includeThrottle` - Default: `true` - Indicates if the Throttle is available on the joystick.
- `bool includeAccelerator` - Default: `true` - Indicates if the Accelerator is available on the joystick.
- `bool includeBrake` - Default: `true` - Indicates if the Brake is available on the joystick.
- `bool includeSteering` - Default: `true` - Indicates if the Steering is available on the joystick.

The following constants define the default values for the constructor parameters listed above:

- `JOYSTICK_DEFAULT_REPORT_ID` is set to `0x03`
- `JOYSTICK_DEFAULT_BUTTON_COUNT` is set to `32`
- `JOYSTICK_DEFAULT_HATSWITCH_COUNT` is set to `2`

### Joystick.begin(bool initAutoSendState)

Starts emulating a game controller connected to a computer. By default, all methods update the game controller state immediately. If `initAutoSendState` is set to `false`, the `Joystick.sendState` method must be called to update the game controller state.

### Joystick.end()

Stops the game controller emulation to a connected computer (Note: just like the Arduino `Keyboard.h` and `Mouse.h` libraries, the `end()` function does not actually do anything).

### Joystick.setXAxisRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the X axis. Default: `0` to `1023`

### Joystick.setXAxis(int32_t value)

Sets the X axis value. See `setXAxisRange` for the range.

### Joystick.setYAxisRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the Y axis. Default: `0` to `1023`

### Joystick.setYAxis(int32_t value)

Sets the Y axis value. See `setYAxisRange` for the range.

### Joystick.setZAxisRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the Z axis. Default: `0` to `1023`

### Joystick.setZAxis(int32_t value)

Sets the Z axis value. See `setZAxisRange` for the range.

### Joystick.setRxAxisRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the X axis rotation. Default: `0` to `1023`

### Joystick.setRxAxis(int32_t value)

Sets the X axis rotation value. See `setRxAxisRange` for the range.

### Joystick.setRyAxisRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the Y axis rotation. Default: `0` to `1023`

### Joystick.setRyAxis(int32_t value)

Sets the Y axis rotation value. See `setRyAxisRange` for the range.

### Joystick.setRzAxisRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the Z axis rotation. Default: `0` to `1023`

### Joystick.setRzAxis(int32_t value)

Sets the Z axis rotation value. See `setRzAxisRange` for the range.

### Joystick.setRudderRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the Rudder. Default: `0` to `1023`

### Joystick.setRudder(int32_t value)

Sets the Rudder value. See `setRudderRange` for the range.

### Joystick.setThrottleRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the Throttle. Default: `0` to `1023`

### Joystick.setThrottle(int32_t value)

Sets the Throttle value. See `setThrottleRange` for the range.

### Joystick.setAcceleratorRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the Accelerator. Default: `0` to `1023`

### Joystick.setAccelerator(int32_t value)

Sets the Accelerator value. See `setAcceleratorRange` for the range.

### Joystick.setBrakeRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the Brake. Default: `0` to `1023`

### Joystick.setBrake(int32_t value)

Sets the Brake value. See `setBrakeRange` for the range.

### Joystick.setSteeringRange(int32_t minimum, int32_t maximum)

Sets the range of values that will be used for the Steering. Default: `0` to `1023`

### Joystick.setSteering(int32_t value)

Sets the Steering value. See `setSteeringRange` for the range.

### Joystick.setButton(uint8_t button, uint8_t value)

Sets the state (`0` or `1`) of the specified button (range: `0` - (`buttonCount - 1`)). The button is the 0-based button number (i.e. button #1 is `0`, button #2 is `1`, etc.). The value is `1` if the button is pressed and `0` if the button is released.

### Joystick.pressButton(uint8_t button)

Press the indicated button (range: `0` - (`buttonCount - 1`)). The button is the 0-based button number (i.e. button #1 is `0`, button #2 is `1`, etc.).

### Joystick.releaseButton(uint8_t button)

Release the indicated button (range: `0` - (`buttonCount - 1`)). The button is the 0-based button number (i.e. button #1 is `0`, button #2 is `1`, etc.).

### Joystick.setHatSwitch(int8_t hatSwitch, int16_t value)

Sets the value of the specified hat switch. The hatSwitch is 0-based (i.e. hat switch #1 is `0` and hat switch #2 is `1`). The value is from 0° to 360°, but in 45° increments. Any value less than 45° will be rounded down (i.e. 44° is rounded down to 0°, 89° is rounded down to 45°, etc.). Set the value to `JOYSTICK_HATSWITCH_RELEASE` or `-1` to release the hat switch.

### Joystick.sendState()

Sends the updated joystick state to the host computer. Only needs to be called if `AutoSendState` is `false` (see `Joystick.begin` for more details).