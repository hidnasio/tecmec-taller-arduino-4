#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 reader(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  reader.PCD_Init();
  Serial.println(F("Init================"));
}

void loop() {
  if ( ! reader.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! reader.PICC_ReadCardSerial()) {
    return;
  }

  reader.PICC_DumpToSerial(&(reader.uid));
}
