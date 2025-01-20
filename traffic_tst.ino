#include <SoftwareSerial.h>

SoftwareSerial mySerial(13, 15); // RX, TX

int T = A0;
int P;

#define BLYNK_TEMPLATE_ID "TMPLoc7y1vYG"
#define BLYNK_DEVICE_NAME "traffic light"
#define BLYNK_AUTH_TOKEN "O1kc3WbGzvfbz7yzFDRZunZt84L3_1xb"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

float resolution=3.3/1023;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "gowtham";  // type your wifi name
char pass[] = "gowtham.";  // type your wifi password

BlynkTimer timer;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, tempvalue);
   timer.setInterval(200L, pulse);
}

void loop() { // run over and over

  Blynk.run();
  timer.run();
}



void tempvalue() {
  float temperature = ((analogRead(A0) * resolution) * 100)+29.89;

  // Print the temperature in the Serial Monitor:
  Serial.print(temperature);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("C");
  Blynk.virtualWrite(V1, temperature);
  delay(1000); // wait a second between readings

}
/*void comm(){
  if (mySerial.available()) {
    //Serial.write(mySerial.read());
    temp = mySerial.read();
    Serial.println(temp);
    Blynk.virtualWrite(V1, temp);
  }
}*/
void pulse(){
  P=random(70,78);
  Serial.println(P);
  Blynk.virtualWrite(V0, P);
  delay(100);
  
}
