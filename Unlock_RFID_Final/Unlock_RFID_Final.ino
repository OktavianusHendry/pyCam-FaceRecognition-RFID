#include <BleKeyboard.h>
#include <SPI.h>
#include <MFRC522.h> // RFID library

BleKeyboard bleKeyboard;

int led = 4;

int RST_PIN = 22; //reset pin
int SS_PIN = 21; //slave select pin

int data, flag = 2;

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

void setup() {
  pinMode(led, OUTPUT);

  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card

  Serial.begin(9600);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  
}

void loop() {

  if (!mfrc522.PICC_IsNewCardPresent()){
    return;
  }
  //Select one of the cards
  if(!mfrc522.PICC_ReadCardSerial()){
    return;
  }
  String content= "";
  byte letter;

  for (byte i=0; i < mfrc522.uid.size; i++){
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  while( Serial.available())
  {
    data = Serial.read();

    if (data == '1')
    {
      flag = 1;
    }
    else if(data == '0')
    {
      flag = 0;
    }

  }

  if(bleKeyboard.isConnected() && content.substring(1) == "32 E9 AD 21" && flag == 0) {
    digitalWrite(led, HIGH);

    bleKeyboard.write(KEY_RETURN);
    delay(250);

    Serial.println("Sending '011003'...");
    bleKeyboard.print("011003");

    delay(100);

    Serial.println("Sending Enter key...");
    bleKeyboard.write(KEY_RETURN);
    digitalWrite(led, LOW);
    flag = 2; //untuk mengembalikan ke awal agar tidak mengalami bug yaitu ttep terdetect owner walaupun tidak ada owner

 }else{
    delay(300);
    digitalWrite(led, LOW);
    digitalWrite(LED_BUILTIN, LOW);
 }

  delay(100);
}
