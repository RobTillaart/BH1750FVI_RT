# BH1750FVI_RT

Arduino library for BH1750FVI (GY-30) 16 bit I2C Lux sensor

## Description

The BH1750FVI is a 16 bit lux sensor with an I2C interface
It is possible to detect a wide range from 0.11 - 100000 lux.

To be able to support this wide range, the sensor can operate in three modi.

| ID | Mode | Integration time | Resolution | Notes |
|:----:|:----:|:----:|:----:|:----|
| 0 | LOW | 16 ms | 4.0 Lux | to measure very bright light |
| 1 | HIGH | 120 ms | 1.0 lux | default |
| 2 | HIGH2 | 120 ms | 0.5 lux | to measure very dim light |

Furthermore one can set a correction factor to reduce / increase the
integration time of the sensor.
The factor should be between 0.45 - 3.68.
It can be used to increase the working range like very bright or very low light conditions.
Another aplication is to correct the transparancy of material, or the type of light used.

Note that the typical integration time will differ if the correction factor is changed.
The **isReady()** an **getLux()** functions keep track of the adjustment needed.

## Interface hardware

Library was tested with a breakout board.

```
//  breakout BH1750FVI / GY-30
//
//      +-----------------------+
//  GND |o                      |
//  ADD |o                      |
//  SDA |o                      |
//  SCL |o                      |
//  VCC |o                      |
//      +-----------------------+
//
// ADD = ADDRESS:
//   0 = 0x23
//   1 = 0x5C
//
```
The sensor works on 2.4 - 3.6 volt so be careful not to connect directly to 5.0 volt.
(Note: the breakout board was 5 volt tolerant)

## Interface API

- **BH1750FVI(address, dataPin, clockPin)**  ESP constructor with I2C parameters
- **BH1750FVI(address, TwoWire \*wire = &Wire)** constructor for other platforms
- **getRaw()** reads the lux sensor,
- **getLux()** reads the lux sensor and corrects for correctionFactor and for HIGH2 mode,
- **getError()** get the latest error, mainly for debugging,
- **powerOn()** wakes up the sensor,
- **powerOff()** set sensor to sleep,
- **reset()** resets the dataregister to 0, effectively removing last measurement.
- **getMode()** gets the mode set by one of the set functions. See table above.
- **setContHighRes()** continuous mode in HIGH resolution
- **setContHigh2Res()** continuous mode in HIGH2 resolution
- **setContLowRes()** continuous mode in LOW resolution
- **setOnceHighRes()** single shot mode in HIGH resolution
- **setOnceHigh2Res()** single shot mode in HIGH2 resolution
- **setOnceLowRes()** single shot mode in LOW resolution
- **isReady()** can be used to check if the sensor is ready.
This is based on a calculated time, the sensor does not have a means to indicate ready directly.
Needed only for the single shot modi.
The function **isReady()** takes the correctionfactor into account.

Please read datasheet P11 about details of the correction factor.
- **changeTiming(uint8_t val)** 69 is default = BH1750FVI_REFERENCE_TIME
- **setCorrectionFactor(float f)** prefered wrapper around changeTiming f = 0.45 .. 3.68
- **getCorrectionFactor()** returns the correction factor.
Note this can differ as it is stores as an integer internally.

## Ideas

**Angle sensitivity**
The lux sensor is really sensitive for the angle of the light. If one makes measurements
outside the position of the sun changes during the day and this function could provide
means to correct that.
- **setAngle(x, y)** add an angle correction factor (datasheet p3, fig 4&5)
This involves 2 angles with very similar characteristic.
- **getAngleX()** **getAngleY()**
- **getAngleFactor()** returns cumulative effect 0..1

**Spectral Sensitivity**
Spectral sensitivity is quite substantial. (datasheet p3, fig 1)
Can be used for correction of light filters.
- **void setSpectral(int wavelength)** set wavelength ==> not linear, lookuptable?
- **int getSpectral()** returns wavelength

**Temperature Sensitivity**
The reference temperature of the sensor = 20°C.
The effect of temperature is small 2.5% per 60°C ==> 1% per 24°C
so only on either a hot roof or on a icy cold day the effect is
- **setTemperature(int T)** (datasheet P3 fig7)
- **getTemperature()** returns T

**Intelligent isReady()**
After a **getLux()** call one can clean the dataregister explicitly with **reset()**.
Then a call to **isReady()** fetches data and as long as data equals zero the sensor is 
not ready.

**DVI interface**
To investigate, sort of external reset?


## Operation

See samples...
