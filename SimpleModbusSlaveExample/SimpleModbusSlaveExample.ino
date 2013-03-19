#include <SimpleModbusSlave.h>
#include <Servo.h> 

/* This example code has 9 holding registers. 6 analogue inputs, 1 button, 1 digital output
   and 1 register to indicate errors encountered since started.
   Function 5 (write single coil) is not implemented so I'm using a whole register
   and function 16 to set the onboard Led on the Atmega328P.
   
   The modbus_update() method updates the holdingRegs register array and checks communication.

   Note:  
   The Arduino serial ring buffer is 128 bytes or 64 registers.
   Most of the time you will connect the arduino to a master via serial
   using a MAX485 or similar.
 
   In a function 3 request the master will attempt to read from your
   slave and since 5 bytes is already used for ID, FUNCTION, NO OF BYTES
   and two BYTES CRC the master can only request 122 bytes or 61 registers.
 
   In a function 16 request the master will attempt to write to your 
   slave and since a 9 bytes is already used for ID, FUNCTION, ADDRESS, 
   NO OF REGISTERS, NO OF BYTES and two BYTES CRC the master can only write
   118 bytes or 59 registers.
 
   Using the FTDI USB to Serial converter the maximum bytes you can send is limited 
   to its internal buffer which is 60 bytes or 30 unsigned int registers. 
 
   Thus:
 
   In a function 3 request the master will attempt to read from your
   slave and since 5 bytes is already used for ID, FUNCTION, NO OF BYTES
   and two BYTES CRC the master can only request 54 bytes or 27 registers.
 
   In a function 16 request the master will attempt to write to your 
   slave and since a 9 bytes is already used for ID, FUNCTION, ADDRESS, 
   NO OF REGISTERS, NO OF BYTES and two BYTES CRC the master can only write
   50 bytes or 25 registers.
 
   Since it is assumed that you will mostly use the Arduino to connect to a 
   master without using a USB to Serial converter the internal buffer is set
   the same as the Arduino Serial ring buffer which is 128 bytes.
*/
 

// Using the enum instruction allows for an easy method for adding and 
// removing registers. Doing it this way saves you #defining the size 
// of your slaves register array each time you want to add more registers
// and at a glimpse informs you of your slaves register layout.

//////////////// registers of your slave ///////////////////
enum 
{     
  // just add or remove registers and your good to go...
  // The first register starts at address 0
  ADC0,  // @ 0
  ADC1,  // @ 1
  ADC2,  // @ 2
  ADC3,  // @ 3
  ADC4,  // @ 4
  ADC5,  // @ 5
  
  GPO02, // @ 6
  GPO03, // @ 7
  GPO04, // @ 8
  GPO05, // @ 9
  GPO06, // @ 10
  GPO07, // @ 11

  GPI08, // @ 12
  GPI09, // @ 13
  GPI10, // @ 14
  GPI11, // @ 15
  GPI12, // @ 16
  
  SERVO, // @ 17

  TOTAL_ERRORS,
  // leave this one
  TOTAL_REGS_SIZE 
  // total number of registers for function 3 and 16 share the same register array
};

Servo myservo;  // create servo object to control a servo 

// servo position
#define CLOSED 142
#define OPENED 42
int previousServoPosition = CLOSED;

unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array


////////////////////////////////////////////////////////////

void setup()
{
  
  // GPIO setup

  // 2-> 7 DIGIGTAL OUTPUT  
  for (byte i=2;i<8;i++) 
  {
    pinMode(i, OUTPUT);  
  }
  
  // 8 -> 12 DIGIGTAL INPUT
  for (byte i=8;i<13;i++)
  {
    pinMode(i, INPUT);  
  }

  myservo.attach(13);
  myservo.write(previousServoPosition);
  
  // setup the serial link and the modbus lib
  Serial.begin(9600);  
  delay(50);
  
  modbus_configure(9600, 1, 2, TOTAL_REGS_SIZE);

  delay(50);
  Serial.println("Ready") ;

}

void loop()
{
  // modbus_update() is the only method used in loop(). It returns the total error
  // count since the slave started. You don't have to use it but it's useful
  // for fault finding by the modbus master.
  holdingRegs[TOTAL_ERRORS] = modbus_update(holdingRegs);
  
  for (byte i = 0; i < 6; i++)
  {
    holdingRegs[i] = analogRead(i);
    delay(10);
    holdingRegs[i] = analogRead(i);
    delay(10);
  }
  
  // write GPO2 to 7 from the modbus register status
  for (byte i = 0; i < 6; i++)
  {
    digitalWrite(i+2,holdingRegs[i+6] == 0 ? LOW : HIGH); 
  }
  
  // set the modubs register from the GPI8 to 12
  for (byte i = 0; i < 5; i++)
  {
    holdingRegs[i+12] = digitalRead(i+8); 
  }
  
  // servo control
  if (holdingRegs[17])
  {
    if(previousServoPosition == CLOSED)
    {
      while(previousServoPosition > OPENED) 
      {
        myservo.write(previousServoPosition--);
        delay (20);
      }
    }
  } else {
    if(previousServoPosition == OPENED)
    {
      while(previousServoPosition < CLOSED)
      {
        myservo.write(previousServoPosition++);
        delay (20);
      }
    }
  }
}

