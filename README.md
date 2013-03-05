mihini-greenhouse-demo
======================

The SimpleModbusSlaveExample Arduino sketch enables a Modbus slave on an Arduino board.
It depends on the simple-modbus Arduino library that you need to download from [here] (https://code.google.com/p/simple-modbus/downloads/list) and [install](http://arduino.cc/en/Guide/Libraries) in your Arduino environment.

When running, the sketch will expose the following Modbus holding registers on its serial port:
* #0 - A0 (input)
* #1 - A1 (input)
* #2 - A2 (input)
* #3 - A3 (input)
* #4 - A4 (input)
* #5 - A5 (input)
* #6 - D10 (output)
* #7 - D7 (input)
* #8 - # of errors (input)


See http://git.eclipse.org/c/mihini/org.eclipse.mihini.samples.git/ for Mihini and Corona apps
