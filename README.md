# Capacitance Meter with Bluetooth LE reading possibilities using an Adafruit Feather nRF52

Repo for a project with the goal of using an Adafruit Feather nRF52 to measure capacitances and to transmit the signal via Bluetooth Low Energy.
This repo also contains an Android App, developed with MIT App Inventor, for reading the signal.

## Implementation


### Capacitance Measurement

My interest was in measuring small capacitances.
For this, I used the approach proposed in this [post](https://wordpress.codewrite.co.uk/pic/2014/01/21/cap-meter-with-arduino-uno/), 
and modify it in order to use an Adafruit Feather nRF52.

As explained in the original post, this is a pretty simple approach that works reasonably well for capacitances in the order of pF.
It makes use of the fact that microcontroller board will always present a stray capacitance.
By connecting the capacitor of interest in series with this stray capacitance e.g., between two analog pins (see scheme below), 
the voltage on the output pin will settle to within 1% of it’s final value few ns after raising the voltage of the input pin from zero to some high value. 
The value to which the voltage of the output pin will settle is proportional to the ration between the capacitance to be measured and the total capacitance i.e., the capacitance of interest plus the stray capacitace, times the high voltage value in the input pin.

This approach requires estimating the stray capacitance. This can be done just by connecting to the board a known capacitor, and use the same approach to estimate the stray capacitance instead.

### Scheme

The setup is similar to that proposed in the original post for Arduino Uno, but using an Adafruit Feather nRF52:

![scheme](AdafruitFeathernRF52CapacitanceMeter_bb.png)

### Reading data through a serial port

The repo includes the code to read the capacitance data through a serial port. The code is found in the file Serial_Capacitance.ino within the Serial_Capacitance folder.

It can be uploaded to the microcontroller with the [Arduino IDE](https://www.arduino.cc/en/Main/Software_). Be aware that in order to do so, you will need first to [install](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup) 
the corresponding package in the IDE.

The first thing you will need to do is to calculate the stray capacitance, and use this value in the code. For this, in the set up above use a capacitor of known value.
Then in the code, comment the following line:

```
//float capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);
```

and uncomment the line inmediately after:

```
float capacitance = 4.7 * (1023.0-val)/(val*1.0);
```

In this line, change 4.7 by the value of the capacitor you have used.

Upload the code, and read the value provided by the serial port. For this you can use the Arduino IDE Serial Monitor. I have also worked on a [Python GUI](https://github.com/JSotres/serialReaderPython) 
that you can use for the same purpose.
