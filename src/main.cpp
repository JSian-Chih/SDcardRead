#include <Arduino.h>



/*

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 This example code is in the public domain.
   
 */
 
#include <SPI.h>
#include <SD.h>

// int chipSelect = 10;
int chipSelect = 14;
File myFile;

// Teensy 3.5 & 3.6 & 4.1 on-board: BUILTIN_SDCARD


void setup()
{
  Serial.begin(115200);
    while (!Serial) {
    ; // wait for serial port to connect.
  }
  delay(3000);
  Serial.print("TTT SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  // open the file. 
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
 // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
     Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
   // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop()
{
 // nothing happens after setup
}