# HMC5883L - Arduino I2C library

C++ library for HMC5883L magnetometer for I2C communication with Arduino Wire library. Main features:

- read raw data,
- read scaled data,
- self test calibration,
- soft and hard iron compensation,
- some minor changes.

The library is intended to work **without any user interference**, just open [project](https://github.com/MatthewPatyk/HMC5883L-Arduino-I2C-library/blob/master/HMC5883L_.atsln) and upload working [example](https://github.com/MatthewPatyk/HMC5883L-Arduino-I2C-library/blob/master/HMC5883L_/HMC5883L_.ino) and use it.

Library uses [I2C Interface](https://github.com/MatthewPatyk/I2C-Interface-for-Arduino-Wire-Library), [I2C Sensor Interface](https://github.com/MatthewPatyk/I2C-Sensor-Interface) to simplify and unify working with I2C devices. The library also uses [Status Class](https://github.com/MatthewPatyk/Status-Class) which is optional.

## Getting Started

The working example for this library is written in [Atmel Studio 7](http://www.microchip.com/mplab/avr-support/atmel-studio-7) with [Visual Micro](https://www.visualmicro.com/) addon. But **it is possible to run it with Arduino IDE** by [adding files to project](https://www.arduino.cc/en/Guide/Environment#toc8) (probably there will be need to change the `#include` paths).

### Prerequisites

- Software:
  - [Atmel Studio 7](http://www.microchip.com/mplab/avr-support/atmel-studio-7) (tested) or Visual Studio,
  - [Visual Micro](https://www.visualmicro.com/) addon for above AS7 or VS.
- Hardware:
  - Arduino Due (tested) or Arduino Uno (any ATmega 328P) board,
  - HMC5883L board or any IMU sensor with HMC5883L.

### Wiring

| HMC5883L board | Due board |   Uno board    |
| :------------: | :-------: | :------------: |
|      DRDY      |   19\*    | any free pin\* |
|      SCL       | SCL (21)  |    SCL (A4)    |
|      SDA       | SDA (20)  |    SDA (A5)    |
|    VCC 3.3V    |   3.3V    |      3.3V      |
|     VCC 5V     |  - \*\*   |       5V       |
|      GND       |    GND    |      GND       |

\*To change pin number use `HMC5883L_A_DATA_READY_PIN` define in `Config.h` file.

\*\*The Due MCU cannot be exposed to the voltage above 3.3V level!

## Example

To see a real-life example open AS7 project file `HMC5883L_.atsln` and upload the `HMC5883L_.ino` to a micro-controller. You should see something like that on Serial Monitor (baud rate = 115200):

```plaintext
2	Serial initialized with baudrate = 115200
167	Found HMC5883L searching device with ID = 0x1e
179	X = 381.32	Y = 61.95	Z = -528.25
185	X = 381.32	Y = 61.95	Z = -528.25
190	X = 382.15	Y = 61.95	Z = -523.16
196	X = 383.21	Y = 63.79	Z = -526.71
...
```

### HMC5883L output rate

The library by default provide the fastest output rate, it is about `160 Hz`, by using `DDRY` HMC5883L pin.

### Calibration process

Due to manufacturing process, magnetometers have some problems with the data quality. In other words, to get the best accuracy, you need to calibrate it.

There are [two kind of problems](https://www.vectornav.com/support/library/magnetometer):

- soft iron,
- hard iron.

The library provide the way to obtain magnetic data from magnetometer and use them in [MATLAB](https://github.com/MatthewPatyk/MATLAB-Magnetometer-Hard-and-Soft-Iron-Compensation-Algorithm) script to calculate soft and hard iron compensation parameters. Read the instructions [here](https://github.com/MatthewPatyk/MATLAB-Magnetometer-Hard-and-Soft-Iron-Compensation-Algorithm).

The result of this calibration is shown below:

![Result](https://raw.githubusercontent.com/MatthewPatyk/MATLAB-Magnetometer-Hard-and-Soft-Iron-Compensation-Algorithm/master/Results/Result.png)

### Polling

`HMC5883L::getDataReadyFlag()` method can be polling in loop, which provide the fastest readout. There is a mechanism using external interrupts without blocking the processor.

```cpp
if(Magnetometer.getDataReadyFlag())
{
	Magnetometer.read();
	...
}
```
