#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 22 //reset pin
#define SS_PIN 21 //slave select pin
#define led 4


MFRC522 mfrc522(SS_PIN, RST_PIN); //declare MFRC522


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  mfrc522.PCD_Init();
  pinMode(led, OUTPUT);
  Serial.println("Put RFID Tag/Card");

}

void loop() {
  // looking for new card
  if (!mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  //Select one of the cards
  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }
  //Show UID for Serial Monitor

  Serial.print("UID Tag: ");
  String content= "";
  byte letter;
  for (byte i=0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] <0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();

  if(content.substring(1) == "32 E9 AD 21")//change here the UID of the Card for access
  {
    Serial.println("Access Granted");
    Serial.println();
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
  } 
  else{
    Serial.println("Access Denied");
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
  }
}
