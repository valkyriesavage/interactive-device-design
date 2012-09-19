/**************************************************************************/
/*! 
    @file     readMifare.pde
    @author   Adafruit Industries
	@license  BSD (see license.txt)

    This example will wait for any ISO14443A card or tag, and
    depending on the size of the UID will attempt to read from it.
   
    If the card has a 4-byte UID it is probably a Mifare
    Classic card, and the following steps are taken:
   
    - Authenticate block 4 (the first block of Sector 1) using
      the default KEYA of 0XFF 0XFF 0XFF 0XFF 0XFF 0XFF
    - If authentication succeeds, we can then read any of the
      4 blocks in that sector (though only block 4 is read here)
	 
    If the card has a 7-byte UID it is probably a Mifare
    Ultralight card, and the 4 byte pages can be read directly.
    Page 4 is read by default since this is the first 'general-
    purpose' page on the tags.


This is an example sketch for the Adafruit PN532 NFC/RFID breakout boards
This library works with the Adafruit NFC breakout 
  ----> https://www.adafruit.com/products/364
 
Check out the links above for our tutorials and wiring diagrams 
These chips use SPI to communicate, 4 required to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

*/
/**************************************************************************/

#include <Adafruit_PN532.h>

#define SCK  (2)
#define MOSI (3)
#define SS   (4)
#define MISO (5)

Adafruit_PN532 nfc(SCK, MISO, MOSI, SS);
uint8_t incomingScore[16] = {'#',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // score to be read from the game
// DEBUG uint8_t incomingScore[16] = {'#','1','2','3','4','$',0,0,0,0,0,0,0,0,0,0};
void setup(void) {
  Serial.begin(9600);
//  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
//    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
//  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
//  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
//  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  
//  Serial.println("Waiting for an ISO14443A Card ...");
}


void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  
  uint8_t dataRead[16]; 
  // try and get a score to write from the game
  int i = 1;
  int digits2Read = Serial.available();
  //int digits2Read = 2;
  while (digits2Read > 0) {
    incomingScore[i] = Serial.read();
    //incomingScore[i] = '5';
    digits2Read--;
    i++;
  //  Serial.print("I received a score: ");
  //  Serial.println(incomingScore[i], DEC);
  }
  if (i<16) {
    incomingScore[i] = '$';
  }
    
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success) {
    // Display some basic information about the card
//    Serial.println("Found an ISO14443A card");
//    Serial.print("  UID Length: ");Serial.print(uidLength, DEC);Serial.println(" bytes");
//    Serial.print("  UID Value: ");
//    nfc.PrintHex(uid, uidLength);
//    Serial.println("");
    
    if (uidLength == 4)
    {
      // We probably have a Mifare Classic card ... 
//      Serial.println("Seems to be a Mifare Classic card (4 byte UID)");
	  
      // Now we need to try to authenticate it for read/write access
      // Try with the factory default KeyA: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
//      Serial.println("Trying to authenticate block 4 with default KEYA value");
      uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	  
	  // Start with block 4 (the first block of sector 1) since sector 0
	  // contains the manufacturer data and it's probably better just
	  // to leave it alone unless you know what you're doing
      success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya);
	  
      if (success)
      {
//        Serial.println("Sector 1 (Blocks 4..7) has been authenticated");
//        uint8_t dataRead[16]; 
//        // try and get a score to write from the game
//        uint8_t incomingScore = 0;
//        if (Serial.available() > 0) {
//          incomingScore = Serial.read();
//          Serial.print("I received a score: ");
//          Serial.println(incomingScore, DEC);
//        }
        	
        uint8_t successRead = nfc.mifareclassic_ReadDataBlock(4, dataRead); // first read
        uint8_t successWrite = nfc.mifareclassic_WriteDataBlock (4, incomingScore); // then write
		
        if (successRead)
        {
          // Data seems to have been read from the card ... spit it out
//            Serial.println("Reading Block 4:");
            nfc.PrintHexChar(dataRead, 16);
//            Serial.println("");
		  
          // Wait a bit before reading the card again
          delay(1000);
        }
        else
        {
//          Serial.println("Ooops ... unable to read the requested block.  Try another key?");
        }
        if (successWrite)
        {
          // Data seems to have been written to the card ... spit it out
//          Serial.println("Just wrote to Block 4:");
//          nfc.PrintHexChar(dataWrite, 16);
          // Writing the score out to the game
//          Serial.print(dataWrite[0]);
//          Serial.println("");
		  
          // Wait a bit before writing to the card again
          delay(1000);
        }
        else
        {
//          Serial.println("Ooops ... unable to write to the requested block.  Try another key?");
        }
      }
      else
      {
//        Serial.println("Ooops ... authentication failed: Try another key?");
      }
    }
    
    if (uidLength == 7)
    {
      // error
//      Serial.println("I didnt expect this type of card.");
    }
  }
}

