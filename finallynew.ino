

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>
const char* token   = "RfPhCOhGK7JiwrGly4E5XdB27vx16ZhmjPZ7YmxSa2E";    // Token ที่ได้จาก Line Notify
const char* mes = "พบกลุ่มควัน";    //ข้อความที่ต้องการให้แสดง
const char* tel = "0903290163";    //เบอร์โทรศัพท์
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);   // IP ของ Arduino
IPAddress myDns(8, 8, 8, 8);      // DNS แนะนำให้ใช้ 8.8.8.8 เป็นของ Google
EthernetClient client;
IPAddress server(103, 233, 194, 42); //เชื่อมต่อแบบ IP
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 10L * 1000L;

char auth[] = "WFO_GQXT79G56Y2rU4ioxgAWyMD7DzUu";  // ต้องแก้ไข
BlynkTimer timer;
#define W5100_CS  10
#define Pump A5
#define HumiditySensor A3
#define ON LOW
#define OFF HIGH
#define smokePin  A4
#define Tds  A2

int HumidityValue , HumidityValueBlynk;
BLYNK_WRITE(V1) {
  int pinValue = param.asInt();

  if (pinValue == 1 ) {
    digitalWrite(Pump , ON);
  }
  else {
    digitalWrite(Pump, OFF);
  }
}
void myTimerEvent()
{
  Blynk.virtualWrite(V2, HumidityValueBlynk);
}
BLYNK_READ(V1)
{
  Blynk.virtualWrite(V1, analogRead(A1));
}

BLYNK_READ(V0)
{
  Blynk.virtualWrite(V0, analogRead(A0));
}


void setup()
{
  Ethernet.begin(mac, ip, myDns);
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  pinMode(smokePin, INPUT);
  while (!Serial) {
  }
  delay(3000);
  pinMode(Pump , OUTPUT);
  digitalWrite(Pump, OUTPUT);
  pinMode(HumiditySensor, INPUT);
  pinMode(Tds, INPUT);
  digitalWrite(Pump , OFF);
  Serial.begin(9600);
  Blynk.begin(auth);
  timer.setInterval(1000L, myTimerEvent);
}
void httpRequest() {
  client.stop();
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    client.print("GET /~line/line.php?token=");
    client.print(token);
    client.print("&mes=");
    client.print(mes);
    client.print("&tel=");
    client.println(tel);
    client.println(" HTTP/1.1");
    client.println("Host: www.arduino.cc");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

  } else {
    Serial.println("connection failed");
  }
}

void loop() {
 Serial.println(analogRead(Tds));
Serial.println(analogRead(smokePin));

if (analogRead(smokePin) > 1200) {         //เช็คปุ่ม D2
  if (millis() - lastConnectionTime > postingInterval) {
    
    httpRequest();
    delay(5000);
  }
} else {
  delay(5000);
  Serial.println("ไม่พบควัน");
 

}
HumidityValueBlynk = analogRead(HumiditySensor);
Serial.println(HumidityValueBlynk);
if (HumidityValueBlynk > 700) {

  digitalWrite(Pump , ON);
  delay(5000);
  digitalWrite(Pump , OFF);
}
else {
  HumidityValueBlynk = 100;
}
Blynk.run();
timer.run();
}
