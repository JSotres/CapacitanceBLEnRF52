# Capacitance Meter with Bluetooth LE reading possibilities using an Adafruit Feather nRF52

This is a project where I used an Adafruit Feather nRF52 to measure capacitances and to transmit the signal via Bluetooth Low Energy.
This repo also contains an Android App developed with MIT App Inventor.

## Implementation

My interest was in measuring small capacitances, in the order of pF, and to implement these measurements in sensors that could transmit the data via Bluetooth Low Energy.
For this, I used the approach proposed in this [post](https://wordpress.codewrite.co.uk/pic/2014/01/21/cap-meter-with-arduino-uno/), and modify it in order to use an Adafruit Feather nRF52 rather than an Arduino Uno and to be able to send the monitored data via Bluetooth Low Energy.

### Capacitance Measurement

My interest was in measuring small capacitances.
For this, I used the approach proposed in this [post](https://wordpress.codewrite.co.uk/pic/2014/01/21/cap-meter-with-arduino-uno/), 
and modify it in order to use an Adafruit Feather nRF52.

As explained in the original post, this is a pretty simple approach that works reasonably well for capacitances in the order of pF.
It makes use of the fact that microcontroller board will always present a stray capacitance.
By connecting the capacitor of interest in series with this stray capacitance e.g., between two analog pins (see scheme below), 
the voltage on the output pin will settle to within 1% of it’s final value few ns after raising the voltage of the input pin from zero to some high value. 
The value to which the voltage of the output pin will settle is proportional to the ration between the capacitance to be measured and the total capacitance i.e., the capacitance of interest plus the stray capacitace, times the high voltage value in the input pin.



### Scheme
![scheme](AdafruitFeathernRF52CapacitanceMeter_bb.png)
