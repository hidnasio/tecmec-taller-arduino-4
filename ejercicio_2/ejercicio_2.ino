#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
#define LED 2

MFRC522 reader(SS_PIN, RST_PIN);
byte validUID[4] = {0xF6, 0xB8, 0x2F, 0xF9};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  reader.PCD_Init();
  pinMode(LED, OUTPUT);
}

void loop() {
  if ( ! reader.PICC_IsNewCardPresent() || ! reader.PICC_ReadCardSerial()) {
    return;
  }

  if (reader.uid.uidByte[0] == validUID[0] &&
      reader.uid.uidByte[1] == validUID[1] && 
      reader.uid.uidByte[2] == validUID[2] && 
      reader.uid.uidByte[3] == validUID[3] ) {

    for (byte i = 0; i < 4; i++) {
      validUID[i] = reader.uid.uidByte[i];
    }

    Serial.println(F("Access granted!"));
    printUID(reader.uid.uidByte, reader.uid.size);
    digitalWrite(LED, HIGH);
    delay(2000);
  } else {
    Serial.println(F("Access not granted!"));
    printUID(reader.uid.uidByte, reader.uid.size);
  }
  
  digitalWrite(LED, LOW);
  reader.PICC_HaltA();
}

void printUID(byte *buffer, byte bufferSize) {
  Serial.print(F("UID: "));
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
}
