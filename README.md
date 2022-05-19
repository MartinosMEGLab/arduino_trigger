## Arduino Analog Trigger
Based on code from juangpc.

### Usage:

To create analog triggers, send commands to the serial port of the Arduino device, followed by a new line character (`\n`). As of now, the following commands are recognized:


#### [number]

ex.: 100

Sends a trigger pulse of height [number].

#### w[number]

ex.: w500

Sets the trigger pulse width to [number] milliseconds for all subsequent trigger pulses.
