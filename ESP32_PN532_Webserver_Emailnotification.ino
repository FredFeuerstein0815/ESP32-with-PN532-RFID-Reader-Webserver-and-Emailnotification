#include <PN532Interface.h>
#include <llcp.h>
#include <PN532.h>
#include <PN532_debug.h>
#include <mac_link.h>
#include <emulatetag.h>
#include <snep.h>
#include <string.h>
#include <SoftwareSerial.h>
#include <PN532_SWHSU.h>
#include <PN532.h>

SoftwareSerial SWSerial( 7, 8 ); // RX, TX

PN532_SWHSU pn532swhsu( SWSerial );

PN532 nfc( pn532swhsu );

void setup(void) {

  Serial.begin(115200);

  Serial.println("Starte Programm ...");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();

  if (! versiondata) {

    Serial.print("Kein RFID-Modul gefunden !");

  }

  Serial.print("RFID gefunden:"); Serial.println((versiondata>>24) & 0xFF, HEX);

  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);

  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

  nfc.SAMConfig();

  Serial.println("Warte auf ISO14443A Karte ...");

}

void loop(void) {

  boolean success;

  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID

  uint8_t uidLength;                       // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success) {

    Serial.print("UID Länge: ");Serial.print(uidLength, DEC);Serial.println(" bytes");

    Serial.print("UID: ");

    for (uint8_t i=0; i < uidLength; i++)

    {

      Serial.print(uid[i], HEX);

    }
  
    Serial.println("");

  uint8_t code[4] = { 0x12, 0xAB, 0xC7, 0x89 } ;
  uidLength = 4 ;
  
if( memcmp(uid,code,uidLength) == 0 )
{
   Serial.println( "Passende UID gefunden" ) ;
   digitalWrite(5, HIGH);
   digitalWrite(6, HIGH);
   digitalWrite(9, HIGH);
   digitalWrite(10, HIGH);
   digitalWrite(11, HIGH);
   digitalWrite(12, HIGH);
   digitalWrite(13, HIGH);
   digitalWrite(14, HIGH);
   digitalWrite(15, HIGH);
   digitalWrite(16, HIGH);
   delay(2000);
}

else {Serial.print("Falsche UID");

    delay(30000);}

  }

  else

  {

    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    digitalWrite(14, LOW);
    digitalWrite(15, LOW);
    digitalWrite(16, LOW);

  }
}
