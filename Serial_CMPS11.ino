#include <SoftwareSerial.h>

#define CMPS_GET_VERSION 0x11

#define CMPS_GET_ANGLE8 0x12
#define CMPS_GET_ANGLE16 0x13
#define CMPS_GET_PITCH 0x14
#define CMPS_GET_ROLL 0x15

unsigned char high_byte, low_byte, angle8;
char pitch, roll;
unsigned int angle16;

void setup()
{
  Serial.begin(9600);       // Start serial ports
  Serial1.begin(9600);
  Serial.print("Fin Setup!\n");
}

void loop()
{
  Serial.print("Debut Loop!\n");
 
  Serial1.write(CMPS_GET_ANGLE16);  // Request and read 16 bit angle

  while(Serial1.available() < 2);
  high_byte = Serial1.read();
  low_byte = Serial1.read();
  
  angle16 = high_byte;                // Calculate 16 bit angle
  angle16 <<= 8;
  angle16 += low_byte;
  
  Serial1.write(CMPS_GET_ANGLE8);  // Request and read 8 bit angle
  while(Serial1.available() < 1);
  angle8 = Serial1.read();
  
  Serial1.write(CMPS_GET_PITCH);   // Request and read pitch value
  while(Serial1.available() < 1);
  pitch = Serial1.read();
  
  Serial1.write(CMPS_GET_ROLL);    // Request and read roll value
  while(Serial1.available() < 1);
  roll = Serial1.read();
  
  Serial.print("roll: ");            // Display roll data
  Serial.print(roll, DEC);
  
  Serial.print("    pitch: ");          // Display pitch data
  Serial.print(pitch, DEC);
  
  Serial.print("    angle full: ");       // Display 16 bit angle with decimal place
  Serial.print(angle16 / 10, DEC);
  Serial.print(".");
  Serial.print(angle16 % 10, DEC);
  
  Serial.print("    angle 8: ");        // Display 8bit angle
  Serial.println(angle8, DEC);

  delay(1000);                           // Short delay before next loop
}
