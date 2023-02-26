#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

int led = 4;
int pb = 2;

int data, flag = 2;

boolean status = 0;

void setup() {
  pinMode(pb, INPUT);
  pinMode(led, OUTPUT);

  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
  status = digitalRead(pb);

  while(Serial.available() ){
    data = Serial.read();

    if (data == '1'){
      flag = 1;
    } else if(data == '0'){
      flag = 0;
    }


    delay(500);
    if(bleKeyboard.isConnected() && status == 1 && data == 1) {
      bleKeyboard.write(KEY_RETURN);
      delay(500);

      Serial.println("Sending 'Password'...");
      bleKeyboard.print("123456789"); // Password
      digitalWrite(led, HIGH);

      delay(300);

      Serial.println("Sending Enter key...");
      bleKeyboard.write(KEY_RETURN);
      digitalWrite(led, LOW);
  }
  
    Serial.println("Waiting 5 seconds...");
    delay(500);
    //delay(1000);

 }
  Serial.println(data);
  Serial.println("test while");
  delay(1000);
  
}
