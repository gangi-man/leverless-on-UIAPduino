# Leverless on UIAPduino

## Overview
Leverless on UIAPduino is an implementation of a USB HID game controller for UIAPduino.

## Hardware
Just connect tactile switches to the UIAPduino GPIO pins as shown in the schematic.

<img src="images/leverless-schematic.png" height="280px">

## Building the Firmware
### Prerequisites
This project uses ch32fun. Please install the required tools described on [this page](https://github.com/cnlohr/ch32fun/wiki/Installation) beforehand.

### Submodules
Initialize the submodules with the following command.

```
 git submodule update --init --recursive
```

### Build / Flash
Connect your WCH-LinkE to your PC and the UIAPduino board then run the following commands


```
cd gamepad
make
```

### Test
Connect UIAPDuino to a Windows PC and start joy.cpl

If everything works correctly, the controller will appear.

<img src="images/joy-cpl.png" height="280px">

