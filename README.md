mihini-greenhouse-demo
======================

The SimpleModbusSlaveExample Arduino sketch enables a Modbus slave on an Arduino board.
It depends on the simple-modbus Arduino library that you need to download from [here] (https://code.google.com/p/simple-modbus/downloads/list) and [install](http://arduino.cc/en/Guide/Libraries) in your Arduino environment.

When running, the sketch will expose the following Modbus holding registers on its serial port:
* #00 - A0 (analog input)
* #01 - A1 (analog input)
* #02 - A2 (analog input)
* #03 - A3 (analog input)
* #04 - A4 (analog input)
* #05 - A5 (analog input)
* #06 - D2 (digital output)
* #07 - D3 (digital output)
* #08 - D4 (digital output)
* #09 - D5 (digital output)
* #10 - D6 (digital output)
* #11 - D7 (digital output)
* #12 - D8 (digital input)
* #13 - D9 (digital input)
* #14 - D10 (digital input)
* #15 - D11 (digital input)
* #16 - D12 (digital input)
* #17 - D13 SERVO (digital output, write 1 or 0 for opening or closing the servo)
* #18 - # of errors (input)


See http://git.eclipse.org/c/mihini/org.eclipse.mihini.samples.git/ for Mihini and Corona apps
