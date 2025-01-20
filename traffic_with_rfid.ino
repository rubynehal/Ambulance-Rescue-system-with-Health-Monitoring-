#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

/*lcd*/
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN            9
#define SS_PIN             10

MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;
/*lcd*/
#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 8); // RX, TX
#define temp A0

#define r1 2
#define y1 3
#define g1 A0

#define r2 A1
#define y2 A2
#define g2 A3

#define r3 4
#define y3 5
#define g3 6




void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("patient tracking");
  lcd.setCursor(0, 1);
  lcd.print("using rfid");
  delay(1000);
  lcd.clear();

  pinMode(r1, OUTPUT);
  pinMode(y1, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(y2, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(y3, OUTPUT);
  pinMode(g3, OUTPUT);

  while (!Serial) {
    ;
  }
  mySerial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
  //rfid();
  // pulsevalue();
  // tempread();
  traffic();
}


void rfid() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    //  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    // Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  // Serial.println();
  // Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "F3 1F C7 16")
  {
    digitalWrite(r1, 0);
    digitalWrite(y1, 0);
    digitalWrite(g1, 1);
    digitalWrite(r2, 1);
    digitalWrite(y2, 0);
    digitalWrite(g2, 0);
    digitalWrite(r3, 1);
    digitalWrite(y3, 0);
    digitalWrite(g3, 0);

    lcd.setCursor(0, 0);
    lcd.print("ROAD 1");
    lcd.setCursor(0, 1);
    lcd.print("EMERGENCY");
    delay(5000);
    lcd.clear();
  }

  else if (content.substring(1) == "FA F5 50 BF")
  {
    digitalWrite(r1, 1);
    digitalWrite(y1, 0);
    digitalWrite(g1, 0);
    digitalWrite(r2, 0);
    digitalWrite(y2, 0);
    digitalWrite(g2, 1);
    digitalWrite(r3, 1);
    digitalWrite(y3, 0);
    digitalWrite(g3, 0);

    lcd.setCursor(0, 0);
    lcd.print("ROAD 2");
    lcd.setCursor(0, 1);
    lcd.print("EMERGENCY");
    delay(5000);
    lcd.clear();
  }
  else   {
    return;
    delay(3000);
  }
}


/*void pulsevalue()
  {
  Signal = analogRead(Pulse);
  Serial.println(Signal);
  lcd.setCursor(0, 0);
  lcd.print("pulse value");
  lcd.setCursor(0, 1);
  lcd.print(Signal);
  mySerial.println("heartbeat");
  mySerial.println(Signal);
  delay(1000);
  lcd.clear();
  }*/

void tempread() {
  int reading = analogRead(temp);

  // Convert the reading into voltage:
  float voltage = reading * (5000 / 1024.0);

  // Convert the voltage into the temperature in degree Celsius:
  float temperature = voltage / 10;

  // Print the temperature in the Serial Monitor:
  Serial.print(temperature);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("C");
  lcd.setCursor(0, 0);
  lcd.print("temperature");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  mySerial.println(temperature);
  delay(1000); // wait a second between readings
  lcd.clear();
}

void traffic() {

  lcd.setCursor(0, 0);
  lcd.print("ROAD 1");
  lcd.setCursor(0, 1);
  lcd.print("GREEN");

  digitalWrite(r1, 0); //road 1

  digitalWrite(g2, 0);

  digitalWrite(g3, 0);

  digitalWrite(g1, 1);

  digitalWrite(y1, 0);

  digitalWrite(y2, 0);

  digitalWrite(r3, 1);

  digitalWrite(y3, 0);

  digitalWrite(r2, 1);

  rfid();

  delay(4000);
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("ROAD 2");
  lcd.setCursor(0, 1);
  lcd.print("GET READY");

  digitalWrite(y1, 1); //enables the yellow lights

  digitalWrite(y2, 1);

  digitalWrite(r1, 0);

  digitalWrite(g2, 0);

  rfid();

  delay(1000);
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("ROAD 2");
  lcd.setCursor(0, 1);
  lcd.print("GREEN");
  digitalWrite(g1, 0); //2nd road

  digitalWrite(r2, 0);

  digitalWrite(g3, 0);

  digitalWrite(r1, 1);

  digitalWrite(y1, 0);

  digitalWrite(y2, 0);

  digitalWrite(r3, 1);

  digitalWrite(y3, 0);

  digitalWrite(g2, 1);

  rfid();

  delay(3000);

  lcd.clear();



  rfid();

  lcd.setCursor(0, 0);
  lcd.print("ROAD 3");
  lcd.setCursor(0, 1);
  lcd.print("GET READY");


  digitalWrite(y3, 1); //enables the yellow lights

  digitalWrite(y2, 1);

  digitalWrite(g3, 0);

  digitalWrite(r2, 0);

  digitalWrite(g1, 0);

  rfid();

  delay(1000);
  lcd.clear();


  rfid();
  lcd.setCursor(0, 0);
  lcd.print("ROAD 3");
  lcd.setCursor(0, 1);
  lcd.print("GREEN");

  digitalWrite(r3, 0); //3rd road

  digitalWrite(g1, 0);

  digitalWrite(g2, 0);

  digitalWrite(r1, 1);

  digitalWrite(y1, 0);

  digitalWrite(r2, 1);

  digitalWrite(y2, 0);

  digitalWrite(y3, 0);

  digitalWrite(g3, 1);

  rfid();

  delay(4000);
  lcd.clear();


  rfid();

  lcd.setCursor(0, 0);
  lcd.print("ROAD 1");
  lcd.setCursor(0, 1);
  lcd.print("GET READY");
  digitalWrite(y3, 1); //enables the yellow lights

  digitalWrite(y1, 1);

  digitalWrite(g2, 0);

  digitalWrite(r3, 0);

  digitalWrite(g1, 0);

  rfid();

  delay(1000);
  lcd.clear();

}
